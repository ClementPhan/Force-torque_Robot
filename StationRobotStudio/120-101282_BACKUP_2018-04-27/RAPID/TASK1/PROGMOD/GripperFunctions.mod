MODULE GripperFunctions
 PERS tooldata EGP_40_N_N_B:=[TRUE,[[-0.025,0.1688,213.437],[0.9763,0,0,-0.2164]],[1,[0,-17.55,111.7686],[1,0,0,0],0,0,0]];
     VAR robtarget positionOffset;
     VAR speeddata transport;
     VAR speeddata place;
     PERS wobjdata wobj;
     PERS tooldata gripper;
     !======
     PROC StartGripper()
         Set DO_01;
         WaitTime 0.5;
     ENDPROC
     PROC ShutdownGripper()
         Reset DO_01;
         WaitTime 0.5;
     ENDPROC
     PROC OpenGripper()
         Reset DO_03;
         Set DO_02;
         WaitTime 0.5;
     ENDPROC
     PROC CloseGripper()
         Reset DO_02;
         Set DO_03;
         WaitTime 0.5;
     ENDPROC
     PROC TakeBloc(robtarget posOffset,robtarget position,tooldata toolsetting,speeddata speedTransport,speeddata speedPlace,wobjdata localwobj)
         gripper:=toolsetting;
         transport:=speedTransport;
         place:=speedPlace;
         positionOffset:=posOffset;
         wobj:=localwobj;
         MoveL positionOffset,transport,fine,gripper\WObj:=wobj;
         OpenGripper;
         MoveL position,place,fine,gripper\WObj:=wobj;
         CloseGripper;
         MoveL positionOffset,place,fine,gripper,\WObj:=wobj;
     ENDPROC
     PROC ReleaseBloc(robtarget posOffset,robtarget position,tooldata toolsetting,speeddata speedTransport,speeddata speedPlace,wobjdata localwobj)
         gripper:=toolsetting;
         transport:=speedTransport;
         place:=speedPlace;
         positionOffset:=posOffset;
         wobj:=localwobj;
         MoveL positionOffset,transport,fine,gripper\WObj:=wobj;
         MoveL position,place,fine,gripper\WObj:=wobj;
         OpenGripper;
         MoveL positionOffset,transport,fine,gripper\WObj:=wobj;
     ENDPROC
ENDMODULE
