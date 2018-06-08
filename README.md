# Force-torque_Robot

## Principle

This project is made to enable the real-time correction of the trajectory of an ABB robot (ABB 120 in our case) using a ATI FT sensor.

The computer on which the code is run will get, verify, filter and treat the forces measured by the sensor and output a z coordinate offset to the robot, who will attempt to use it as correction.

## Organisation

All the code or station backup that has to do with the robot is located in [Robot](Robot)

All the code designed to run on the computer is located in in [Computer](Computer)

## Prerequisites

You will need a ABB robot, a ATI sensor with UDP capabilities (almost all of them) and a windows computer (due to the use of winsock) 

The OS of the computer can be changed if you put in the effort to add in the linux headers.
