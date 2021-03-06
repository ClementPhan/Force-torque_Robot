MODULE Serveur

    !***********************************************************
    !
    ! Module : Serveur
    !
    ! Description : Task Serveur en communication avec l'ordinateur et la main task
    !               - PROC ServerCreateAndConnect(string ip, num port) -> Lancement du serveur et connection avec le client (ordinateur)
    !                                                                     Handshake between server and client:
    !                                                                       - Creates socket.
    !                                                                       - Waits for incoming TCP connection
    !               - PROC ParseMsg(string msg) -> Traduction des messages re�us
    !                                              Method to parse the message received from a PC. If correct message, loads values on :
    !                                                - OFFSET
    !                                                - RATIO
    !               - PROC main() -> Boucle de r�ception des messages et envoi via message RMQ vers la main task
    !
    ! Auteur : Nahkriin
    !
    ! Version : 1.0
    !
    !***********************************************************

    ! =============DECLARATIONS============

    ! Communication

    VAR socketdev clientSocket; !Variables serveur
    VAR socketdev serverSocket;
    VAR bool connected:=FALSE;  !Statut de la connexion

    PERS string ipController:= "192.168.1.101"; !robot default IP
    !PERS string ipController:= "192.168.1.99"; !local IP for testing in simulation
    PERS num serverPort:= 5000;

    VAR string receivedString;  !Message recu

    VAR rmqslot destination_slot;   !Variable RMQ
    VAR string msg; !Message envoye

    PERS tasks task_list{2} := [["Serveur"], ["T_ROB1"]];   !Varibales de stnchronisation des tasks
    VAR syncident sync1;

    VAR num msg_ok:=3; !Variable de validite du message

    ! Post-traitement

    VAR string OFFSET:="0"; !Valeurs du message par defaut
    VAR string RATIO:="100";
    
    VAR num offset_int:=0;
    VAR num ratio_int:=100;

    CONST num Gain:=1000000;    !Gain de la communication
    
    VAR clock timer;
    VAR num time;

    PERS bool flag:=FALSE;   !Booleen de declenchement de la correction
    CONST num speedz := 12.61;   !Vitesse de correction verticale (ne d�pend pas de speed !)
    CONST num speed:=10; !Vitesse du TCP (mm/s)

    CONST num resolution:=10; !Correction max entre deux targets (mm)

    VAR num buffer:=0.1; !Temps de buffer pour la correction (s)

    VAR num tau:=120;    !Temps de correction maximal

    ! Mesure Latence

    ! =============DECLARATIONS============

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


    PROC ParseMsg(string msg)

        VAR num length; !Variables du message
        VAR num header;

        VAR num newInd; !Indices de lecture
        VAR num ind:=1;

        VAR string subString;

        VAR bool Conversion;    !Variable de conversion

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
        ratio_int:=100000000;

        IF msg_ok>0 THEN !header=1,2 ou 3 : affectation des valeurs de correction
            newInd := StrMatch(msg,ind," ")+1;
            subString := StrPart(msg,ind,newInd - ind - 1);

            IF msg_ok = 2 THEN ! header = 2 : vitesse uniquement
                Conversion:=StrToVal(subString,ratio_int);

                IF Conversion = FALSE THEN
                    msg_ok:=-1;
                    TPWrite "Message invalide";
                ENDIF

            ELSEIF msg_ok = 1 THEN !header = 1 : offset uniquement
                Conversion:=StrToVal(subString,offset_int);

                IF Conversion = FALSE THEN
                    msg_ok:=-1;
                    TPWrite "Message invalide";
                ELSEIF msg_ok = 3 THEN !header = 3 : ratio et offset
                    ind := newInd;
                    newInd := StrMatch(msg,ind," ")+1;
                    subString := StrPart(msg,ind,newInd - ind - 1);
                    Conversion:=StrToVal(subString,ratio_int);

                    IF Conversion=FALSE THEN
                        msg_ok:=-1;
                        TPWrite "Message invalide";
                    ENDIF

                ENDIF

            ENDIF

        ENDIF

        offset_int:=offset_int/Gain;
        ratio_int:=ratio_int/Gain;

    ENDPROC


    PROC main()

        VAR string MESSAGE;

        ! Lancement du serveur

        ServerCreateAndConnect ipController,serverPort;
        connected:=TRUE;

        WaitSyncTask sync1, task_list; !Synchronisation des deux t�ches
        
        !ClkReset(timer);
        !ClkStart(timer);

        flag:=TRUE; !Top correction

        !Boucle du serveur

        WHILE flag DO

            SocketReceive clientSocket \Str:=receivedString \Time:=WAIT_MAX;
            ParseMsg receivedString;
            TPWrite "Message recu"+receivedString;

            RMQFindSlot destination_slot, "RMQ_T_ROB1";

            IF msg_ok=0 THEN
                MESSAGE:="STOP";
                RMQSendMessage destination_slot, MESSAGE;

                flag:=FALSE;
                SocketSend clientSocket \Str := "Stop!";
                SocketClose clientSocket;
                SocketClose serverSocket;

            ELSEIF msg_ok>0 THEN
                SocketSend clientSocket \Str := "Recvd";
                
!                !Envoi du message RMQ

                OFFSET:=ValToStr(offset_int);
                RATIO:=ValToStr(ratio_int);
                MESSAGE:=OFFSET+" "+RATIO;
        		RMQSendMessage destination_slot, MESSAGE; 
                WaitTime buffer;

                time:=ClkRead(timer);
                IF time>tau THEN
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
