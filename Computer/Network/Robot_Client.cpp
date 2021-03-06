#include "Robot_Client.hpp"

Robot_Client::Robot_Client(void)
{
	network = new ClientTCP(DEFAULT_ADDRESS_TCP, DEFAULT_PORT_TCP); 
}

Robot_Client::Robot_Client(char* address, char* port)
{
	network = new ClientTCP(address, port);
	msgcheck();
}

Robot_Client::~Robot_Client(void)
{
}

bool Robot_Client::readyToSend(void)
{
	if (robotStatus == readyToRecieve)
	{
		return true;
	}
	else
	{
		msgcheck();
		switch (robotStatus)
		{
		case readyToRecieve:
			return true;
			break;
		default:
			return false;
			break;
		}
	}
}

int Robot_Client::sendSTOP()
{
	if (robotStatus != readyToRecieve)
	{
		printf("Robot not ready. Use 'msgcheck' first.\n");
		return 1;
	}
	std::string s = "0 #"; // Code 0 for STOP and recovery
	int iResult = network->sendMessage(s.c_str(), s.length());
	if (iResult != s.length()) //Check for proper message send
	{
		printf("Bad mesage send\n");
		return 1;
	}
	robotStatus = waitingForResponse;
	return 0;
}

int Robot_Client::sendZChange(long ZChange)
{
	if (robotStatus != readyToRecieve)
	{
		printf("Robot not ready. Use 'msgcheck' first.\n");
		return 1;
	}
	std::string s = "1 " + std::to_string(ZChange) + " #"; // Code 1 for Z offset
	int iResult = network->sendMessage(s.c_str(), s.length());
	if (iResult != s.length()) //Check for proper message send
	{
		printf("Bad mesage send\n");
		return 1;
	}
	robotStatus = waitingForResponse;
	return 0;
}

int Robot_Client::sendVChange(long VChange)
{
	if (robotStatus != readyToRecieve)
	{
		printf("Robot not ready. Use 'msgcheck' first.\n");
		return 1;
	}
	std::string s = "2 " + std::to_string(VChange) + " #"; // Code 2 for speed offset
	int iResult = network->sendMessage(s.c_str(), s.length());
	if (iResult != s.length()) //Check for proper message send
	{
		printf("Bad mesage send\n");
		return 1;
	}
	robotStatus = waitingForResponse;
	return 0;
}

int Robot_Client::sendZandVChange(long ZChange, long VChange)
{
	if (robotStatus != readyToRecieve)
	{
		printf("Robot not ready. Use 'msgcheck' first.\n");
		return 1;
	}
	std::string s = "3 " + std::to_string(ZChange) + " " + std::to_string(VChange) + " #"; // Code 3 for speed offset
	int iResult = network->sendMessage(s.c_str(), s.length());
	if (iResult != s.length()) //Check for proper message send
	{
		printf("Bad mesage send\n");
		return 1;
	}
	robotStatus = waitingForResponse;
	return 0;
}

void Robot_Client::msgcheck(void)
{
	// Recieve the ack from the robot and compares
	int iResult = network->recvMessage(recvbuf, recvbuflen);
	if (iResult == -1)
	{
		return;
	}
	if (iResult == 0)
	{
		robotStatus = correctionEnd;
		return;
	}

	// While there are bytes queued for analisis, analyse them.
	while (iResult > 0)
	{
		// If the message is not complete, quit the processing
		if (iResult < 5)
		{
			printf("Non-complete message recieved\n");
			break;
		}

		// Compare the recieved message to all possible messages
		if (strncmp(recvbuf, "Recvd", 5) == 0)
		{
			robotStatus = msgRecieved;
		}
		else if (strncmp(recvbuf, "Ready", 5) == 0)
		{
			robotStatus = readyToRecieve;
		}
		else if (strncmp(recvbuf, "Error", 5) == 0)
		{
			robotStatus = msgError;
		}
		else if (strncmp(recvbuf, "Stop!", 5) == 0)
		{
			robotStatus = correctionEnd;
		}
		else // If there is no correspondance raise error
		{
			robotStatus = networkError;
			break;
		}

		// if there is more than one message queued, move the rest to the front
		iResult = iResult - 5; 
		if (iResult > 0)
		{
			memcpy(recvbuf, recvbuf + 5, iResult);
		}
	}
	return;
}
