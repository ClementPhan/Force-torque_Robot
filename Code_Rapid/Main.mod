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

                VelSet r,speed; !Modifiaction de la vitesse

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
                !TPWrite "Position actuelle du robot : "\Num:=coordonnee;   !Monitoring position

            ENDIF

    	ELSE

    		TPWrite "Message RMQ non valide";

        ENDIF

	ENDTRAP

	TRAP routine_mesure

    	VAR pos position;
    	VAR num coordonnee;

    	position:=CPos(\Tool:=Tool0 \WObj:=WObj0);
    	coordonnee:=position.z;
        TPWrite "position : "\Num:=coordonnee;

    	IF coordonnee>offset+5-0.1 THEN
            TPWrite "position : "\Num:=coordonnee;
    		temps_correction := ClkRead(timer_correction);
    		TPWrite "Temps correction : "\Num:=temps_correction;
            IDelete int;
    		ClkReset timer_correction;
    	ENDIF

	ENDTRAP


    PROC MainduLove()

        CorrCon z_id;	!Connexion du correcteur

		CONNECT rmqint WITH routine;    !Connexion a la routine de correction
		IRMQMessage msg1, rmqint;

		IF mesure THEN
			CONNECT int WITH routine_mesure;    !Connexion a la routine de mesure
			ITimer 0.1, int;
		ENDIF

        RMQEmptyQueue;  !Vidage de la queue RMQ

        %"MainModule:Main"%;

        IDelete rmqint; !Deconnexion
        IDelete int;

        CorrClear;

    ENDPROC

ENDMODULE
