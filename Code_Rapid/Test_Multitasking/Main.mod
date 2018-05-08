MODULE Tache_Principale
    !***********************************************************
    !
    ! Module: Tache_Principale
    !
    ! Description : Correction en Z avec multitasking -> La correction appliquée dans la tâche principale est calculée dans la tâche serveur et est communiquée via RMQ [Interrupt].
    !
    ! Auteur : Nahkriin
    !
    ! Version : 1.0
    !
    !***********************************************************


	VAR intnum rmqint; ! ID de la routine RMQ

    VAR corrdescr z_id; !Variables de correction
    VAR pos write_offset;
    VAR pos total_offset;

	VAR num offset;

	VAR rmqheader rmqheader1;   !Variables message RMQ
	VAR rmqslot rmqslot1;
	VAR rmqmessage rmqmessage1;

    VAR string msg1;    !Data du message RMQ

    PERS bool flag; !Booleen de declenchement de la correction

    VAR bool flag1;
    VAR bool flag2;

    PERS tasks task_list1{2} := [["TestServeur"], ["T_ROB1"]];  !Varibales de stnchronisation des tasks
    VAR syncident sync1;
    VAR syncident sync2;

    CONST num speed:=100;
    VAR num r:=100;

    ! =============DECLARATIONS============
    VAR speeddata MySpeed:=[speed,100,5000,1000];

    CONST jointtarget Targ0:=[[33.91,89.83,-18.86,0,19.03,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];

    CONST robtarget Targ1:=[[418.38,270.47,0],[0,-0.283,0.9591,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ2:=[[418.38,259.68,0],[0,-0.2742,0.9617,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ3:=[[418.38,248.9,0],[0,-0.2651,0.9642,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ4:=[[418.38,238.11,0],[0,-0.2558,0.9667,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ5:=[[418.38,227.33,0],[0,-0.2463,0.9692,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ6:=[[418.38,216.54,0],[0,-0.2365,0.9716,0],[0,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ7:=[[418.38,205.76,0],[0,-0.2266,0.974,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ8:=[[418.38,194.97,0],[0,-0.2163,0.9763,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ9:=[[418.38,184.19,0],[0,-0.2059,0.9786,0],[0,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ10:=[[418.38,173.41,0],[0,-0.1952,0.9808,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ11:=[[418.38,162.62,0],[0,-0.1843,0.9829,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ12:=[[418.38,151.84,0],[0,-0.1732,0.9849,0],[0,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ13:=[[418.38,141.05,0],[0,-0.1619,0.9868,0],[0,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ14:=[[418.38,130.27,0],[0,-0.1504,0.9886,0],[0,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ15:=[[418.38,119.48,0],[0,-0.1386,0.9903,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ16:=[[418.38,108.7,0],[0,-0.1268,0.9919,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ17:=[[418.38,97.91,0],[0,-0.1147,0.9934,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ18:=[[418.38,87.13,0],[0,-0.1025,0.9947,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ19:=[[418.38,76.34,0],[0,-0.0901,0.9959,0],[0,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ20:=[[418.38,65.56,0],[0,-0.0776,0.997,0],[0,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ21:=[[418.38,54.78,0],[0,-0.065,0.9979,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ22:=[[418.38,43.99,0],[0,-0.0524,0.9986,0],[0,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ23:=[[418.38,33.21,0],[0,-0.0396,0.9992,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ24:=[[418.38,22.42,0],[0,-0.0268,0.9996,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ25:=[[418.38,11.64,0],[0,-0.0139,0.9999,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ26:=[[418.38,0.85,0],[0,-0.001,1,0],[0,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ27:=[[418.38,-9.93,0],[0,0.0119,0.9999,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ28:=[[418.38,-20.72,0],[0,0.0247,0.9997,0],[-1,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ29:=[[418.38,-31.5,0],[0,0.0376,0.9993,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ30:=[[418.38,-42.29,0],[0,0.0503,0.9987,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ31:=[[418.38,-53.07,0],[0,0.063,0.998,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ32:=[[418.38,-63.85,0],[0,0.0757,0.9971,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ33:=[[418.38,-74.64,0],[0,0.0882,0.9961,0],[-1,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ34:=[[418.38,-85.42,0],[0,0.1005,0.9949,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ35:=[[418.38,-96.21,0],[0,0.1128,0.9936,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ36:=[[418.38,-106.99,0],[0,0.1249,0.9922,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ37:=[[418.38,-117.78,0],[0,0.1368,0.9906,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ38:=[[418.38,-128.56,0],[0,0.1485,0.9889,0],[-1,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ39:=[[418.38,-139.35,0],[0,0.1601,0.9871,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ40:=[[418.38,-150.13,0],[0,0.1714,0.9852,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ41:=[[418.38,-160.92,0],[0,0.1826,0.9832,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ42:=[[418.38,-171.7,0],[0,0.1935,0.9811,0],[-1,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ43:=[[418.38,-182.48,0],[0,0.2042,0.9789,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ44:=[[418.38,-193.27,0],[0,0.2147,0.9767,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ45:=[[418.38,-204.05,0],[0,0.2249,0.9744,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ46:=[[418.38,-214.84,0],[0,0.235,0.972,0],[-1,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ47:=[[418.38,-225.62,0],[0,0.2448,0.9696,0],[-1,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ48:=[[418.38,-236.41,0],[0,0.2543,0.9671,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ49:=[[418.38,-247.19,0],[0,0.2637,0.9646,0],[-1,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ50:=[[418.38,-257.98,0],[0,0.2728,0.9621,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ51:=[[418.38,-268.76,0],[0,0.2816,0.9595,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ52:=[[418.38,-279.55,0],[0,0.2903,0.9569,0],[-1,0,0,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];
    CONST robtarget Targ53:=[[418.38,-290.33,0],[0,0.2987,0.9543,0],[-1,0,-1,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];

    CONST jointtarget Targ54:=[[-35.74,90.77,-21.87,0,21.09,0],[0,9E+09,9E+09,9E+09,9E+09,9E+09]];

!Routine de reception RMQ et correction

	TRAP routine

        VAR num ind:=1;
        VAR num newind;
        VAR string offset1;
        VAR string ratio1;

        !Partie reception

    	RMQGetMessage rmqmessage1;  !Reception du message RMQ
    	RMQGetMsgHeader rmqmessage1 \Header:=rmqheader1 \SenderId:=rmqslot1;    !Recuperation des informations

    	IF rmqheader1.datatype = "string" AND rmqheader1.ndim = 0 THEN

    		RMQGetMsgData rmqmessage1, msg1;    !Recuperation des donnees
            newind := StrMatch(msg1,ind," ") + 1;
            offset1:= StrPart(msg1,ind,newind - ind -1);

            ind:=newind;
            ratio1:= StrPart(msg1,ind,StrLen(msg1)-ind+1);

            flag1 := StrToVal(offset1, offset);    !Conversion des donnees
            flag2 := StrToVal(ratio1, r);

    	ELSE

    		TPWrite "Message RMQ non valide";

        ENDIF

        !Partie correction

        VelSet r,speed; !Modifiaction de la vitesse

        write_offset.x := 0;
        write_offset.y := 0;
        write_offset.z := offset;

        TPWrite "On corrige"\Num:=offset;
        TPWrite "Ratio vitesse"\Num:=r;
        CorrWrite z_id, write_offset;

        RMQEmptyQueue;

	ENDTRAP
    PROC main()

        CorrCon z_id;	!Connection du correcteur

		CONNECT rmqint WITH routine;    !Connection a la routine de correction
		IRMQMessage msg1, rmqint;

        RMQEmptyQueue;  !Vidage de la queue RMQ

        ConfJ \Off;
        ConfL \Off;

        MoveAbsJ Targ0,MySpeed,z1,Tool0; ! Initialisation : le robot va au point de depart de la trajectoire

        WaitSyncTask sync1, task_list1;  !Synchronisation des deux tâches

        TPWrite "Starting routine."; !Test de declenchement du process

        MoveL Targ1,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ2,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ3,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ4,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ5,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ6,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ7,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ8,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ9,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ10,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ11,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ12,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ13,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ14,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ15,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ16,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ17,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ18,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ19,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ20,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ21,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ22,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ23,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ24,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ25,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ26,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ27,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ28,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ29,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ30,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ31,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ32,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ33,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ34,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ35,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ36,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ37,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ38,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ39,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ40,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ41,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ42,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ43,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ44,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ45,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ46,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ47,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ48,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ49,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ50,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ51,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ52,MySpeed,z1,Tool0\WObj:=WObj0\Corr;
        MoveL Targ53,MySpeed,Fine,Tool0\WObj:=WObj0\Corr;

        TPWrite "Stop routine."; !Test de fin du process
        IDelete rmqint;
        CorrClear;

        MoveAbsJ Targ0,MySpeed,z1,Tool0; !Retour au point de depart

    ENDPROC

ENDMODULE
