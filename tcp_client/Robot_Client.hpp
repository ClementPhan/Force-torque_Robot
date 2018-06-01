#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
#include <sstream>
#include "ClientTCP.hpp"

/*
*	PURPOSE :
*	connecting to an ABB robot
*
*	USE :
*	Create the class object with correct address and port (by default
*	is 192.168.1.2:5000)
*
*	Messages will only be sent when readyToSend(); returns true.
*
*	All data sent has a multiplier of 1 000 000
*	i.e. 1 500 000 for a value of 1.5
*
*
*/

// port to connect sockets through 
#define DEFAULT_PORT_TCP "5000"
#define DEFAULT_ADDRESS_TCP "192.168.1.2"

const int recvbuflen = 25;

// Robot status. Note that msgError indicates a badly formatted message, untreated by the robot while networkError is a non-treatable message recieved by this client.
enum status { unconected, readyToRecieve,waitingForResponse, msgRecieved, msgError, correctionEnd, networkError }; /* State of the robot "msgrecieved" means that another correction has to wait to be given */

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

	bool readyToSend(void);

	// Send commands to the robot.
	// These will not execute unless robotStatus is read to be "readyToRecieve"
	// Call msgcheck to update robotStatus
	int sendSTOP();
	int sendZChange(long Zchange); // Send message to change z coordinate
	int sendVChange(long VChange); // Send message to change speed
	int sendZandVChange(long Zchange, long VChange); // Send message to change z coordinate and speed
};