MODULE Tache_Principale

    !***********************************************************
    !
    ! Module : Main
    !
    ! Description : Main Motion Task
    !               - PROC main() -> Mouvement du Robot avec iterrupt pour correction
    !               - TRAP routine() -> Reception messages RMQ & correction de la trajectoire selon l'axe normal (Z) et de la vitesse
    !
    ! Auteur : Nahkriin
    !
    ! Version : 1.0
    !
    !***********************************************************

    ! =============DECLARATIONS============

    ! Communication

    ! ID de la routine RMQ
    VAR intnum rmqint;

    !Variables message RMQ
    VAR rmqheader rmqheader1;
    VAR rmqslot rmqslot1;
    VAR rmqmessage rmqmessage1;

    !Data du message RMQ
    VAR string msg1;

    !Booleens de conversion
    VAR bool flag1;
    VAR bool flag2;

    !Varibales de stnchronisation des tasks
    PERS tasks task_list{2}:=[["Serveur"],["T_ROB1"]];
    VAR syncident sync1;

    ! Correction

    !Booleen de declenchement de la correction
    PERS bool flag;

    !Variables de correction
    VAR corrdescr z_id;
    VAR pos write_offset;
    VAR pos total_offset;

    !Offset de correction selon l'axe z
    VAR num offset;
    !Ratio de correction de la vitesse
    VAR num r:=100;

    ! Mesure Latence

    VAR clock timer_correction;
    VAR num temps_correction;

    PERS bool mesure;

    VAR intnum int;

    ! Mouvement

    VAR pathrecid safe_id;

    CONST num speed:=10;

    !jointtarget
    VAR jointtarget jointtarget0:=[[7.156115,4.061388,46.760373,5.860299,42.396364,137.713576],[9E9,9E9,9E9,9E9,9E9,9E9]];
    VAR jointtarget jointtarget1:=[[-51.441511,37.582418,0.883601,-0.672067,56.504381,83.954101],[9E9,9E9,9E9,9E9,9E9,9E9]];



    !robtarget
    CONST robtarget robtarget0:=[[246.061131,48.985471,111.512088],[0.040299,-0.923,-0.382319,0.016692],[0,0,1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    CONST robtarget robtarget1:=[[246.100785,47.986266,111.516158],[0.040299,-0.923,-0.382319,0.016692],[0,0,1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    CONST robtarget robtarget2:=[[261.209145,-332.7109,113.066913],[0.040299,-0.923,-0.382319,0.016692],[-1,-1,0,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    CONST robtarget robtarget3:=[[261.16949,-331.711695,113.062843],[0.040299,-0.923,-0.382319,0.016692],[-1,-1,0,0],[9E9,9E9,9E9,9E9,9E9,9E9]];


    !speeddata

    VAR speeddata speeddata0:=[10,572.957795,5000,1000];

    !tooldata

    PERS tooldata ToolOfLove:=[TRUE,[[0.015258,-0.149222,106.919],[0.999048,0.043619,0,0]],[1,[0,0,0.1],[1,0,0,0],0,0,0]];

    !wobjdata

    PERS wobjdata Root:=[False,True,"",[[0,0,0],[1,0,0,0]],[[0,0,0],[1,0,0,0]]];

    !zonedata

    VAR zonedata zonedata0:=[False,1,5,1,5,1,5];

    ! =============FOCNTIONS============

    TRAP routine

        !Indices de lecture
        VAR num ind:=1;
        VAR num newind;

        !Variables de correction
        VAR string offset1;
        VAR string ratio1;

        VAR pos position;
        VAR num coordonnee;

        !Partie reception

        !Reception du message RMQ
        RMQGetMessage rmqmessage1;
        !Recuperation des informations
        RMQGetMsgHeader rmqmessage1\Header:=rmqheader1\SenderId:=rmqslot1;

        IF rmqheader1.datatype="string" AND rmqheader1.ndim=0 THEN

            !Recuperation des donnees
            RMQGetMsgData rmqmessage1,msg1;

            !Arret d'urgence : on revient en arrière et on lève le bras du robot.
            IF msg1="STOP" THEN

                VelSet 50,speed;
                StorePath;
                PathRecMoveBwd\ID:=safe_id\ToolOffs:=[0,0,50];
                Stop;

            ELSE

                newind:=StrMatch(msg1,ind," ")+1;
                offset1:=StrPart(msg1,ind,newind-ind-1);

                ind:=newind;
                ratio1:=StrPart(msg1,ind,StrLen(msg1)-ind+1);

                !Conversion des donnees
                flag1:=StrToVal(offset1,offset);
                flag2:=StrToVal(ratio1,r);

                !Partie correction

                !Modifiaction de la vitesse 
                SpeedRefresh r;

                !Modification de la position
                write_offset.x:=0;
                write_offset.y:=0;
                write_offset.z:=offset;

                !Application de la correction
                CorrWrite z_id,write_offset;

                !Lancement horloge correction
                IF mesure THEN
                    ClkReset timer_correction;
                    ClkStart timer_correction;
                ENDIF

                position:=CPos(\Tool:=Tool0\WObj:=WObj0);
                coordonnee:=position.z;

                !Monitoring correction
                TPWrite "On corrige : "\Num:=offset;
                !TPWrite "Ratio vitesse"\Num:=r;
                TPWrite "Position actuelle du robot : "\Num:=coordonnee;

            ENDIF

        ELSE

            TPWrite "Message RMQ non valide";

        ENDIF

    ENDTRAP


    TRAP routine_mesure

        VAR pos position;
        VAR num coordonnee;

        position:=CPos(\Tool:=ToolOfLove\WObj:=Root);
        coordonnee:=position.z;
        TPWrite "position : "\Num:=coordonnee;

        IF coordonnee>offset-0.1 THEN
            TPWrite "position : "\Num:=coordonnee;
            temps_correction:=ClkRead(timer_correction);
            TPWrite "Temps correction : "\Num:=temps_correction;
            IDelete int;
            ClkReset timer_correction;
        ENDIF

    ENDTRAP


    PROC Main()

        ConfL\On;
        ConfJ\On;
        SingArea\Wrist;

        ! ============= MoveAbsJ ============

        MoveAbsJ jointtarget0,speeddata0,zonedata0,ToolOfLove;
        MoveL robtarget0,speeddata0,zonedata0,ToolOfLove\WObj:=Root;

        !Connexion du correcteur
        CorrCon z_id;

        !Connexion a la routine de correction
        CONNECT rmqint WITH routine;
        IRMQMessage msg1,rmqint;

        !Connexion a la routine de mesure
        IF mesure THEN
            CONNECT int WITH routine_mesure;
            ITimer 0.5,int;
        ENDIF

        !Vidage de la queue RMQ
        RMQEmptyQueue;

        WaitSyncTask sync1,task_list;
        PathRecStart safe_id;

        TPWrite "Start Routine";

        ! ============= MoveL ============

        MoveL robtarget1,speeddata0,zonedata0,ToolOfLove\WObj:=Root\Corr;
        MoveL robtarget2,speeddata0,fine,ToolOfLove\WObj:=Root\Corr;

        PathRecStop;
        flag:=FALSE;

        !Deconnexion
        IDelete rmqint;
        IDelete int;

        CorrClear;

        MoveL robtarget3,speeddata0,zonedata0,ToolOfLove\WObj:=Root;
        MoveAbsJ jointtarget1,speeddata0,zonedata0,ToolOfLove;

    ENDPROC

ENDMODULE
