MODULE Serveur_test

!Variables du serveur

VAR socketdev clientSocket;
VAR socketdev serverSocket;

!PERS string ipController:= "192.168.125.1"; !robot default IP
PERS string ipController:= "192.168.1.99"; !local IP for testing in simulation
PERS num serverPort:= 5000;

PERS tasks task_list1{2} := [["TestServeur"], ["T_ROB1"]];

VAR string OFFSET:="0";
VAR string RATIO:="100";

CONST num Gain:=1000000;

PERS bool flag:=TRUE;

VAR num resolution := 10;
VAR num speed:=100;
VAR num buffer;

VAR clock timer2;
VAR num time2;
VAR num TAU:=60;

VAR num msg_ok:=-1;

!Handshake between server and client:
! - Creates socket.
! - Waits for incoming TCP connection.

PROC ServerCreateAndConnect(string ip, num port)

    VAR string clientIP;

    SocketCreate serverSocket;
    SocketBind serverSocket, ip, port;
    SocketListen serverSocket;
    TPWrite "SERVER: Server waiting for incoming connections ...";

    WHILE SocketGetStatus(clientSocket) <> SOCKET_CONNECTED DO

        SocketAccept serverSocket,clientSocket \ClientAddress:=clientIP \Time:=WAIT_MAX;

        IF SocketGetStatus(clientSocket) <> SOCKET_CONNECTED THEN
            TPWrite "SERVER: Problem serving an incoming connection.";
            TPWrite "SERVER: Try reconnecting.";
        ENDIF

    ENDWHILE

    SocketSend clientSocket \Str:="Ready";
    TPWrite "SERVER: Connected to IP " + clientIP;

ENDPROC

!Method to parse the message received from a PC
!If correct message, loads values on :
! - OFFSET (Correction z)
! - RATIO (Correction vitesse)

PROC ParseMsg(string msg)

    VAR num length;
    VAR num newInd;
    VAR num ind:=1;
    VAR string subString;
    VAR bool Conversion;

    VAR num header;

    VAR num offset_int;
    VAR num ratio_int;

    ! Find the end character

    length:=StrMatch(msg,1,"#");

    IF length>Strlen(msg) THEN

        msg_ok:=-1;
        TPWrite "Message invalide";

    ELSE

        newInd:=StrMatch(msg,ind," ")+1;
        subString:=StrPart(msg, ind, newInd-ind-1);
        Conversion:=StrToVal(subString,header);

        IF Conversion = FALSE OR header>3 THEN

            msg_ok:=-1;
            TPWrite "Message invalide";

        ELSE

            msg_ok:=header;

        ENDIF

    ENDIF

    ind:=newInd;

    offset_int:=0;
    ratio_int:=0;

    IF msg_ok>0 THEN !Correction

        newInd := StrMatch(msg,ind," ")+1;
        subString := StrPart(msg,ind,newInd - ind - 1);

        IF msg_ok = 2 THEN ! Juste ratio de vitesse

            Conversion:=StrToVal(subString,ratio_int);

        ELSE

            Conversion:=StrToVal(subString,offset_int);

            IF msg_ok = 3 THEN !Ratio et offset

                ind := newInd;
                newInd := StrMatch(msg,ind," ")+1;
                subString := StrPart(msg,ind,newInd - ind - 1);
                Conversion:=StrToVal(subString,ratio_int);

            ELSE

                ratio_int:=100000000;

            ENDIF

        ENDIF

    ENDIF

offset_int:=offset_int/Gain;
ratio_int:=ratio_int/Gain;
speed:=speed*ratio_int;

OFFSET:=ValToStr(offset_int);
RATIO:=ValToStr(ratio_int);

ENDPROC

PROC main()

    VAR bool connected:=FALSE;

    VAR string receivedString;
    VAR string msg;

    VAR rmqslot destination_slot;

    VAR syncident sync1;

    VAR string MESSAGE;

    ! Lancement du serveur

    ServerCreateAndConnect ipController,serverPort;
    connected:=TRUE;

    WaitSyncTask sync1, task_list1;

    flag:=TRUE;

    ClkReset timer2;
    ClkStart timer2;

    !Boucle du serveur

    WHILE TRUE AND flag DO
        SocketReceive clientSocket \Str:=receivedString \Time:=WAIT_MAX;
        ParseMsg receivedString;
        IF msg_ok>0 THEN
            SocketSend clientSocket \Str := "Recvd";

            !Envoi du message RMQ

    		RMQFindSlot destination_slot, "RMQ_T_ROB1";
            MESSAGE:=OFFSET+" "+RATIO;
    		RMQSendMessage destination_slot, MESSAGE;

            buffer:=resolution/speed;
            WaitTime buffer;

            time2:=ClkRead(timer2);
            TPWrite ValtoStr(time2);

            IF time2>TAU THEN
                flag:=FALSE;
                SocketSend clientSocket \Str := "Stop!";
                SocketClose clientSocket;
                SocketClose serverSocket;
            ELSE
                SocketSend clientSocket \Str := "Ready";
            ENDIF
        ELSE
            SocketSend clientSocket \Str := "Error";
        ENDIF

    ENDWHILE

ENDPROC


ENDMODULE
