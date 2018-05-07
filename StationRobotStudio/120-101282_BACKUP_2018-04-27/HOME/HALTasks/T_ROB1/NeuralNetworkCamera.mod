MODULE NeuralNetworkCamera
  PERS num robotStatus:=0;
       PERS wobjdata blockWobj:=[FALSE,TRUE,"",[[0,0,0],[1,0,0,0]],[[335,258,0],[0.446198,0,0,-0.894934]]];
       VAR speeddata identificationSpeed;
       PERS tooldata usedTool;
       VAR robtarget usedTargetNNC;
       ! ==============PROCEDURES=============
       PROC FindBlock(tooldata providedTool, robtarget providedTargetNNC, speeddata idSpeed)
           usedTool := providedTool;
           usedTargetNNC := providedTargetNNC;
           identificationSpeed := idSpeed;
           PredL;
           WaitTime 1;
           ToolCrop;
           WaitTime 1;
           PredP;
           WaitTime 1;
       ENDPROC
       PROC PredL()
           ConfJ\Off;
           ConfL\Off;
           RobotStatus:=0;
           RobotStatus:=1;
           !predL_concat
           WaitUntil RobotStatus=0;
           RobotStatus:=2;
           !setWobj2
           WaitUntil RobotStatus=0;
           MoveL usedTargetNNC,identificationSpeed,z1,usedTool\WObj:=blockWobj;
       ENDPROC
       PROC ToolCrop()
           !set tool coords
           RobotStatus:=3;
           WaitUntil RobotStatus=0;
           !tool-centered crop pict and display it 
           RobotStatus:=4;
           WaitUntil RobotStatus=0;
           !pred P
           RobotStatus:=5;
           !predP_concat
           WaitUntil RobotStatus=0;
       ENDPROC
       PROC PredP()
           ConfJ\Off;
           ConfL\Off;
           RobotStatus:=0;
           RobotStatus:=6;
           !setWobj
           WaitUntil RobotStatus=0;
           MoveL usedTargetNNC,identificationSpeed,fine,usedTool\WObj:=blockWobj;
       ENDPROC
ENDMODULE
