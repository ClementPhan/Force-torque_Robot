#include "Robot_Client.hpp"

Robot_Client::Robot_Client(void)
{
	network = new ClientTCP();
}

Robot_Client::Robot_Client(char* address, char* port)
{
	network = new ClientTCP(address, port);
}

Robot_Client::~Robot_Client(void)
{
}

int Robot_Client::sendZChange(int ZChange)
{
	char* message;
	int iResult = 0;
	std::string s; // Used to convert from int to char*
	s = "1 " + std::to_string(ZChange) + " #"; // Code 1 for Z offset
	const char* temp = s.c_str();
	message = new char[s.length()];
	memcpy(message, temp, s.length());
	printf(message);
	iResult = network->sendMessage(message, sizeof(message));
	if (iResult != s.length())
	{
		printf("Bad mesage send");
		return 1;
	}
	return 0;
}

int Robot_Client::sendVChange(int VChange)
{
	char* message;
	int iResult = 0;
	std::string s; // Used to convert from int to char*
	s = "2 " + std::to_string(VChange) + " #"; // Code 2 for speed offset
	const char* temp = s.c_str();
	message = new char[s.length()];
	memcpy(message, temp, s.length());
	printf(message);
	iResult = network->sendMessage(message, sizeof(message));
	if (iResult != s.length())
	{
		printf("Bad mesage send");
		return 1;
	}
	return 0;
}

int Robot_Client::sendZandVChange(int ZChange, int VChange)
{
	char* message;
	int iResult = 0;
	std::string s; // Used to convert from int to char*
	s = "3 " + std::to_string(ZChange)+ " " + std::to_string(VChange) + " #"; // Code 3 for speed offset
	const char* temp = s.c_str();
	message = new char[s.length()];
	memcpy(message, temp, s.length());
	printf(message);
	iResult = network->sendMessage(message, sizeof(message));
	if (iResult != s.length())
	{
		printf("Bad mesage send");
		return 1;
	}
	return 0;
}
