MODULE Clock_test
	!***********************************************************
    !
    ! Module:  Clock_test
    !
    ! Description : Tache serveur qui envoie les messages RMQ de correction
    !
    ! Auteur : Nahkriin
    !
    ! Version : 1.0
    !
    !***********************************************************

    VAR clock timer1;   !Variables de l'horloge
    VAR num time:=0;

    VAR num TAU1:=2;
    VAR num TAU2:=3;
    VAR num offset_1:=0;

    PERS bool flag:=TRUE;   !Booleen de declenchement de la correction

    VAR rmqslot destination_slot;   !Slot RMQ de la tache principale

    VAR string msg; !Message RMQ

    PERS tasks task_list{2} := [["Serveur"], ["T_ROB1"]];   !Varibales de stnchronisation des tasks
    VAR syncident sync1;
    VAR syncident sync2;




    PROC main()

        WaitSyncTask sync1, task_list;  !Synchronisation des deux tâches

        flag:=TRUE; !Declenchement de la correction

        ClkStart timer1;    !Top horloge

        WHILE TRUE AND flag DO

            msg := ValToStr(offset_1);  !Conversion des donnees

            !Envoi du message RMQ

			RMQFindSlot destination_slot, "RMQ_T_ROB1";
			RMQSendMessage destination_slot, msg;
            !Buffer
            WaitTime 0.5;

            time:=ClkRead(timer1); !Lecture horloge

            IF time>TAU1 AND time<TAU2 THEN
                offset_1:=20;

            ELSEIF time>TAU2 THEN
                flag:=FALSE;
                TPWrite "On ne corrige plus";

            ENDIF

        ENDWHILE

    ENDPROC

ENDMODULE
