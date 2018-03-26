MODULE Clock_test
	!***********************************************************
    !
    ! Module:  Clock_test
    !
    ! Description : Serveur qui envoie les valeurs de correction à Main en tout instant.
    !
    ! Auteur : Nahkriin
    !
    ! Version : 1.0
    !
    !***********************************************************
	

    VAR clock timer2;   !Variables de l'horloge
    VAR num time2:=0;
    
    VAR num TAU:=1;  !Variables du pic
    PERS num offset2:=0;
    
    
    
    PROC main()
        
        ClkStart timer2;    !Top horloge

        WHILE TRUE DO
            
            time2:=ClkRead(timer2);
            
            IF time2>=TAU THEN
                
                offset2:=50;    !pic up
                WaitTime 1;
                
                offset2:=-50;   !pic down
                WaitTime 1;
                
                ClkReset timer2;    !Restart horloge
                ClkStart timer2;
                
            ELSE
                
                offset2:=0;
                
            ENDIF
            
        ENDWHILE


    ENDPROC

ENDMODULE