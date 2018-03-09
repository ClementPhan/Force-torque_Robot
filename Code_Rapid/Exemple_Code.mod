MODULE Exemple_Code
    
    !***********************************************************
    !
    ! Module :  Exemple_Code
    !
    ! Description :
    ! Exemple de script en Rapid avec des corrections de trajectoire sur un chemin du robot donné
    !
    ! Auteur : Nahkriin
    !
    ! Version : 1.0
    !
    !***********************************************************
    
    ! hori_sig and vert_sig are analog signals defined in system parameters.
    CONST num TARGET_DIST := 5;
    CONST num SCALE_FACTOR := 0.5;
    VAR intnum intno1;
    VAR corrdescr hori_id;
    VAR corrdescr vert_id;
    VAR pos total_offset;
    VAR pos write_offset;
    VAR bool conFlag;

    PROC PathRoutine()
        ! Connect to the correction generators for horizontal and vertical correction.
        CorrCon hori_id;
        CorrCon vert_id;
        conFlag := TRUE;
        ! Setup a 5 Hz timer interrupt. The trap routine will read the sensor values and compute the path corrections.
        CONNECT intno1 WITH ReadSensors;
        ITimer\Single, 0.2, intno1;
        ! Position for start of contour tracking
        MoveJ p10,v100,z10,tool1;
        ! Run MoveL with both vertical and horizontal correction.
        MoveL p20,v100,z10,tool1\Corr;
        ! Read the total corrections added by all connected correction generators.
        total_offset := CorrRead();
        ! Write the total vertical correction on the FlexPendant.
        TPWrite "The total vertical correction is:"
        \Num:=total_offset.z;
        ! Disconnect the correction generator for vertical correction.
        ! Horizontal corrections will be unaffected.
        CorrDiscon vert_id;
        conFlag := FALSE;
        ! Run MoveL with only horizontal interrupt correction.
        MoveL p30,v100,z10,tool1\Corr;
        ! Remove all outstanding connected correction generators.
        ! In this case, the only connected correction generator is the one for horizontal correction.
        CorrClear;
        ! Remove the timer interrupt.
        IDelete intno1;
    ENDPROC

    TRAP ReadSensors
        VAR num horiSig;
        VAR num vertSig;
        ! Compute the horizontal correction values and execute the correction.
        horiSig := hori_sig;
        write_offset.x := 0;
        write_offset.y := (hori_sig - TARGET_DIST)*SCALE_FACTOR;
        write_offset.z := 0;
        CorrWrite hori_id, write_offset;
        IF conFlag THEN
        ! Compute the vertical correction values and execute the correction.
        write_offset.x := 0;
        write_offset.y := 0;
        write_offset.z := (vert_sig - TARGET_DIST)*SCALE_FACTOR;
        CorrWrite vert_id, write_offset;
        ENDIF
        !Setup interrupt again
        IDelete intnol;
        CONNECT intno1 WITH ReadSensors;
        ITimer\single, 0.2, intno1;
    ENDTRAP

ENDMODULE