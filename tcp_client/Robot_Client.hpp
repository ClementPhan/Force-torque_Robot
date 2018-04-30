#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
#include <sstream>
#include "ClientTCP.hpp"

class Robot_Client
{
private:
	ClientTCP* network;

public:
	Robot_Client(void);
	Robot_Client(char * address, char * port);
	~Robot_Client(void);

	int sendZChange(int Zchange);
	int sendVChange(int VChange);
	int sendZandVChange(int Zchange, int VChange);
};