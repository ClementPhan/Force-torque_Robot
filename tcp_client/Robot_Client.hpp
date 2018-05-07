#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
#include <sstream>
#include "ClientTCP.hpp"

const int recvbuflen = 25;

// Robot status. Note that msgError indicates a badly formatted message, untreated by the robot while networkError is a non-treatable message recieved by this client.
enum status { unconected, readyToRecieve, msgRecieved, msgError, correctionEnd, networkError }; /* State of the robot "msgrecieved" means that another correction has to wait to be given */

class Robot_Client
{
private:
	ClientTCP* network; // Socket and socket information
	status robotStatus = unconected;

	char recvbuf[recvbuflen]; //updated by msgcheck()
	void msgcheck(void); // Recieves, verifes and updates robotStatus according to recived responses

public:
	Robot_Client(void);
	Robot_Client(char * address, char * port);
	~Robot_Client(void);

	status getRobotStatus()
	{
		return robotStatus;
	}

	bool readyToSend(void);

	// Send commands to the robot.
	// These will not execute unless robotStatus is read to be "readyToRecieve"
	// Call msgcheck to update robotStatus
	int sendZChange(int Zchange); // Send message to change z coordinate
	int sendVChange(int VChange); // Send message to change speed
	int sendZandVChange(int Zchange, int VChange); // Send message to change z coordinate and speed
};