#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
#include "ClientUDP.h"

class FT_Client
{
private:
	bool isStreamStarted = false;
	
	ClientUDP* network;

public:
	FT_Client(void);
	FT_Client(char * address, char * port);
	~FT_Client(void);

	int startStream();

	int stopStream();

	int update(int donnees_capteur[6]);
};