MODULE MainModule
! ================INFOS================
! MainModule
! by IRB120_02
! 04/04/2018
! Generated with HAL 0053
! c Thibault Schwartz 2011-2014
! c HAL Robotics ltd 2015
! http://www.hal-robotics.com
! =====================================


! =============DECLARATIONS============
 VAR speeddata MySpeed:=[100,100,5000,1000];
 PERS tooldata EGP_40_N_N_B:=[TRUE,[[-0.025,0.1688,213.437],[0.9763,0,0,-0.2164]],[1,[0,-17.55,111.7686],[1,0,0,0],0,0,0]];
 CONST robtarget Targ000:=[[300,-92.31,66],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ001:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ002:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ003:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ004:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ005:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ006:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ007:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ008:=[[503.47,-276.94,66],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ009:=[[503.47,-276.94,16],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0010:=[[503.47,-276.94,66],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0011:=[[300,-92.31,66],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ010:=[[300,-96.97,64.72],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ011:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ012:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ013:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ014:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ015:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ016:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ017:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ018:=[[410.44,-290.9,64.72],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ019:=[[410.44,-290.9,14.72],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0110:=[[410.44,-290.9,64.72],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0111:=[[300,-96.97,64.72],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ020:=[[300,-105.55,64.85],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ021:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ022:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ023:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ024:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ025:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ026:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ027:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ028:=[[319.43,-316.66,64.85],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ029:=[[319.43,-316.66,14.85],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0210:=[[319.43,-316.66,64.85],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0211:=[[300,-105.55,64.85],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ030:=[[300,-108.49,65.41],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ031:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ032:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ033:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ034:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ035:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ036:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ037:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ038:=[[225.53,-325.46,65.41],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ039:=[[225.53,-325.46,15.41],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0310:=[[225.53,-325.46,65.41],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0311:=[[300,-108.49,65.41],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ040:=[[300,-102.45,65.86],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ041:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ042:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ043:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ044:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ045:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ046:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ047:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ048:=[[132.99,-307.34,65.86],[-0.0013,0.8129,0.5823,-0.0009],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ049:=[[132.99,-307.34,15.86],[-0.0013,0.8129,0.5823,-0.0009],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0410:=[[132.99,-307.34,65.86],[-0.0013,0.8129,0.5823,-0.0009],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0411:=[[300,-102.45,65.86],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ050:=[[300,-89.22,66],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ051:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ052:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ053:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ054:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ055:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ056:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ057:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ058:=[[47.28,-267.65,66],[0,0.8666,0.499,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ059:=[[47.28,-267.65,16],[0,0.8666,0.499,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0510:=[[47.28,-267.65,66],[0,0.8666,0.499,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0511:=[[300,-89.22,66],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ060:=[[300,-89.21,106.75],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ061:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ062:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ063:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ064:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ065:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ066:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ067:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ068:=[[463.44,-267.63,106.75],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ069:=[[463.44,-267.63,56.75],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0610:=[[463.44,-267.63,106.75],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0611:=[[300,-89.21,106.75],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ070:=[[300,-93.86,105.47],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ071:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ072:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ073:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ074:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ075:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ076:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ077:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ078:=[[370.41,-281.59,105.47],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ079:=[[370.41,-281.59,55.47],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0710:=[[370.41,-281.59,105.47],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0711:=[[300,-93.86,105.47],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ080:=[[300,-102.45,105.6],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ081:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ082:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ083:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ084:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ085:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ086:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ087:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ088:=[[279.4,-307.35,105.6],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ089:=[[279.4,-307.35,55.6],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0810:=[[279.4,-307.35,105.6],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0811:=[[300,-102.45,105.6],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ090:=[[300,-105.38,106.16],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ091:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ092:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ093:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ094:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ095:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ096:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ097:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ098:=[[185.5,-316.15,106.16],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ099:=[[185.5,-316.15,56.16],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0910:=[[185.5,-316.15,106.16],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ0911:=[[300,-105.38,106.16],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ100:=[[300,-99.34,106.61],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ101:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ102:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ103:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ104:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ105:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ106:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ107:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ108:=[[92.96,-298.03,106.61],[-0.0013,0.8129,0.5823,-0.0009],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ109:=[[92.96,-298.03,56.61],[-0.0013,0.8129,0.5823,-0.0009],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1010:=[[92.96,-298.03,106.61],[-0.0013,0.8129,0.5823,-0.0009],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1011:=[[300,-99.34,106.61],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ110:=[[300,-86.69,146.83],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ111:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ112:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ113:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ114:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ115:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ116:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ117:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ118:=[[409.17,-260.07,146.83],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ119:=[[409.17,-260.07,96.83],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1110:=[[409.17,-260.07,146.83],[0.0092,0.7328,0.6804,0.0086],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1111:=[[300,-86.69,146.83],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ120:=[[300,-91.34,145.55],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ121:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ122:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ123:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ124:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ125:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ126:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ127:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ128:=[[316.13,-274.03,145.55],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ129:=[[316.13,-274.03,95.55],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1210:=[[316.13,-274.03,145.55],[0.0012,0.6002,0.7999,0.0016],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1211:=[[300,-91.34,145.55],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ130:=[[300,-99.93,145.68],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ131:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ132:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ133:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ134:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ135:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ136:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ137:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ138:=[[225.13,-299.79,145.68],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ139:=[[225.13,-299.79,95.68],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1310:=[[225.13,-299.79,145.68],[-0.0015,0.6258,0.7799,-0.0019],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1311:=[[300,-99.93,145.68],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ140:=[[300,-102.86,146.24],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ141:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ142:=[[-147,284,117],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ143:=[[-94.82,284,169.18],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ144:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ145:=[[-32,300,34],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ146:=[[3.36,300,69.36],[-0.2706,-0.6533,0.6533,0.2706],[0,0,-1,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ147:=[[300,300,66],[0,0,1,0],[0,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ148:=[[131.22,-308.59,146.24],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ149:=[[131.22,-308.59,96.24],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1410:=[[131.22,-308.59,146.24],[-0.0022,0.7241,0.6897,-0.0021],[-1,-1,0,0],[0,9E9,9E9,9E9,9E9,9E9]];
 CONST robtarget Targ1411:=[[300,-102.86,146.24],[0,0,1,0],[-1,0,0,0],[0,9E9,9E9,9E9,9E9,9E9]];


! ==============PROCEDURES=============
 PROC Main()
  ConfJ \Off;
  ConfL \Off;
  Set DO1;
  Reset DO3;
  Set DO2;
  MoveL Targ000,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  takeblock;
  MoveL Targ001,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ002,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ003,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ004,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ005,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ006,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ007,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ008,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ009,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ0010,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0011,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  takeblock;
  MoveL Targ010,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ011,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ012,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ013,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ014,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ015,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ016,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ017,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ018,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ019,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ0110,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  takeblock;
  MoveL Targ0111,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ020,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ021,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ022,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ023,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ024,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ025,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ026,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ027,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ028,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ029,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  takeblock;
  MoveL Targ0210,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0211,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ030,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ031,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ032,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ033,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ034,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ035,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ036,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ037,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ038,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ039,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  takeblock;
  WaitTime(1);
  MoveL Targ0310,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0311,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ040,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ041,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ042,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ043,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ044,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ045,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ046,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ047,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ048,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ049,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  takeblock;
  Reset DO2;
  WaitTime(1);
  MoveL Targ0410,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0411,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ050,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ051,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ052,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ053,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ054,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ055,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ056,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ057,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ058,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ059,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  takeblock;
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ0510,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0511,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ060,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ061,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ062,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ063,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ064,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ065,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ066,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ067,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ068,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ069,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  takeblock;
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ0610,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0611,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ070,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ071,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ072,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ073,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ074,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ075,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ076,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ077,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ078,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ079,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  takeblock;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ0710,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0711,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ080,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ081,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ082,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ083,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ084,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ085,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ086,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ087,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ088,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  takeblock;
  MoveL Targ089,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ0810,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0811,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ090,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ091,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ092,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ093,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ094,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ095,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ096,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ097,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  takeblock;
  MoveL Targ098,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ099,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ0910,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ0911,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ100,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ101,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ102,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ103,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ104,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ105,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ106,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  takeblock;
  MoveL Targ107,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ108,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ109,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ1010,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ1011,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ110,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ111,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ112,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ113,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ114,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ115,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  takeblock;
  MoveL Targ116,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ117,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ118,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ119,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ1110,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ1111,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ120,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ121,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ122,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ123,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ124,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  takeblock;
  MoveL Targ125,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ126,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ127,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ128,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ129,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ1210,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ1211,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ130,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ131,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ132,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ133,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ134,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  takeblock;
  WaitTime(1);
  MoveL Targ135,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ136,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ137,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ138,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ139,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ1310,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ1311,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ140,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ141,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ142,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ143,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ144,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  MoveL Targ145,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ146,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ147,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ148,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ149,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Close Tool
  WaitTime(1);
  Set DO3;
  Reset DO2;
  WaitTime(1);
  MoveL Targ1410,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  MoveL Targ1411,MySpeed,z1,EGP_40_N_N_B\WObj:=WObj0;
  !Open Tool
  WaitTime(1);
  Reset DO3;
  Set DO2;
  WaitTime(1);
  Reset DO1;
 ENDPROC
ENDMODULE
