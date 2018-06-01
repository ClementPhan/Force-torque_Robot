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

	VAR intnum rmqint; ! ID de la routine RMQ

	VAR rmqheader rmqheader1;   !Variables message RMQ
	VAR rmqslot rmqslot1;
	VAR rmqmessage rmqmessage1;

    VAR string msg1;    !Data du message RMQ

    VAR bool flag1; !Booleens de conversion
    VAR bool flag2;

   	PERS tasks task_list{2} := [["Serveur"], ["T_ROB1"]];  !Varibales de stnchronisation des tasks
    VAR syncident sync1;

    ! Correction

    PERS bool flag; !Booleen de declenchement de la correction

    VAR corrdescr z_id; !Variables de correction
    VAR pos write_offset;
    VAR pos total_offset;

	VAR num offset; !Offset de correction selon l'axe z
    VAR num r:=100; !Ratio de correction de la vitesse

	! Mesure Latence

	VAR clock timer_correction;
	VAR num temps_correction;

	PERS bool mesure;

	VAR intnum int;

    ! Mouvement

    VAR pathrecid safe_id;
    
    CONST num speed:=50;
    
    !jointtarget
    
    VAR jointtarget In:=[[-42.798717,72.821707,-33.570111,1.039762,50.706712,89.778158],[9E9,9E9,9E9,9E9,9E9,9E9]];

    !robtarget
    
    CONST robtarget robtarget0:=[[393.19573,-364.272527,11.385258],[0.003876,0.930961,-0.364964,0.009886],[-1,0,1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    CONST robtarget robtarget1:=[[393.643113,-272.219283,11.126808],[0.003462,0.954527,-0.297899,0.011094],[-1,0,1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    CONST robtarget robtarget2:=[[394.090495,-180.16604,10.868357],[0.002668,0.977027,-0.212744,0.012251],[-1,0,1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    CONST robtarget robtarget3:=[[394.537878,-88.112797,10.609907],[0.001438,0.993886,-0.109633,0.01304],[-1,0,1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    CONST robtarget robtarget4:=[[394.985261,3.940446,10.351456],[-0.000065,0.999902,0.004987,0.013099],[0,-1,1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];
    CONST robtarget robtarget5:=[[395.432644,95.99369,10.093006],[-0.001473,0.992843,0.118784,0.012311],[0,-1,1,0],[9E9,9E9,9E9,9E9,9E9,9E9]];

    !speeddata
    
    VAR speeddata speeddata0:=[speed,572.957795,5000,1000];

    !tooldata
    
    PERS tooldata ToolOfLove:=[True,[[0.015258,-0.149222,99.918848],[1,0,0,0]],[1,[0,0,0.1],[1,0,0,0],0,0,0]];

    !wobjdata
    
    PERS wobjdata Root:=[False,True,"",[[0,0,0],[1,0,0,0]],[[0,0,0],[1,0,0,0]]];

    !zonedata
    
    VAR zonedata zonedata0:=[False,1,5,1,5,1,5];

    ! =============FOCNTIONS============

	TRAP routine

        VAR num ind:=1; !Indices de lecture
        VAR num newind;

        VAR string offset1; !Variables de correction
        VAR string ratio1;

        VAR pos position;
        VAR num coordonnee;

        !Partie reception

    	RMQGetMessage rmqmessage1;  !Reception du message RMQ
    	RMQGetMsgHeader rmqmessage1 \Header:=rmqheader1 \SenderId:=rmqslot1;    !Recuperation des informations

    	IF rmqheader1.datatype = "string" AND rmqheader1.ndim = 0 THEN

    		RMQGetMsgData rmqmessage1, msg1;    !Recuperation des donnees

            IF msg1="STOP" THEN !Arret d'urgence : on revient en arrière et on lève le bras du robot.

                VelSet 50,speed;
                StorePath;
                PathRecMoveBwd \ID:=safe_id \ToolOffs:=[0,0,50];
                Stop;

            ELSE

                newind := StrMatch(msg1,ind," ") + 1;
                offset1:= StrPart(msg1,ind,newind - ind -1);

                ind:=newind;
                ratio1:= StrPart(msg1,ind,StrLen(msg1)-ind+1);

                flag1 := StrToVal(offset1, offset);    !Conversion des donnees
                flag2 := StrToVal(ratio1, r);

                !Partie correction

                SpeedRefresh r; !Modifiaction de la vitesse
                
                !WaitTime 0.3; !Latence modification de la vitesse : on préfère une montée puis un offset ou une ligne puis offset ?

                write_offset.x := 0;    !Modification de la position
                write_offset.y := 0;
                write_offset.z := offset;

                CorrWrite z_id, write_offset;   !Application de la correction

                IF mesure THEN	!Lancement horloge correction
					ClkReset timer_correction;
					ClkStart timer_correction;
				ENDIF

                position:=CPos(\Tool:=Tool0 \WObj:=WObj0);
                coordonnee:=position.z;

                TPWrite "On corrige : "\Num:=offset;    !Monitoring correction
                !TPWrite "Ratio vitesse"\Num:=r;
                TPWrite "Position actuelle du robot : "\Num:=coordonnee;   !Monitoring position

            ENDIF

    	ELSE

    		TPWrite "Message RMQ non valide";

        ENDIF

	ENDTRAP

	TRAP routine_mesure

    	VAR pos position;
    	VAR num coordonnee;

    	position:=CPos(\Tool:=ToolOfLove \WObj:=Root);
    	coordonnee:=position.z;
        TPWrite "position : "\Num:=coordonnee;

    	IF coordonnee>offset-0.1 THEN
            TPWrite "position : "\Num:=coordonnee;
    		temps_correction := ClkRead(timer_correction);
    		TPWrite "Temps correction : "\Num:=temps_correction;
            IDelete int;
    		ClkReset timer_correction;
    	ENDIF

	ENDTRAP


    PROC Main()

        ConfL \On;
        ConfJ \On;
        SingArea \Wrist;

        ! ============= MoveAbsJ ============
        
        MoveAbsJ In, speeddata0, zonedata0, ToolOfLove;

        CorrCon z_id;	!Connexion du correcteur

        CONNECT rmqint WITH routine;    !Connexion a la routine de correction
        IRMQMessage msg1, rmqint;

        IF mesure THEN
        	CONNECT int WITH routine_mesure;    !Connexion a la routine de mesure
        	ITimer 0.5, int;
        ENDIF

        RMQEmptyQueue;  !Vidage de la queue RMQ
                
        WaitSyncTask sync1, task_list; 
        PathRecStart safe_id;
        TPWrite "Start Routine";

        ! ============= MoveL ============
        
        MoveL robtarget0, speeddata0, zonedata0, ToolOfLove \WObj:=Root\Corr;
        MoveL robtarget1, speeddata0, zonedata0, ToolOfLove \WObj:=Root\Corr;
        MoveL robtarget2, speeddata0, zonedata0, ToolOfLove \WObj:=Root\Corr;
        MoveL robtarget3, speeddata0, zonedata0, ToolOfLove \WObj:=Root\Corr;
        MoveL robtarget4, speeddata0, zonedata0, ToolOfLove \WObj:=Root\Corr;
        MoveL robtarget5, speeddata0, fine, ToolOfLove \WObj:=Root\Corr;
        

        PathRecStop;

        IDelete rmqint; !Deconnexion
        IDelete int;

        CorrClear;

    ENDPROC

ENDMODULE
