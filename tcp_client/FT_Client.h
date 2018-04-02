#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
#include "ClientNetwork.h"
#include "NetworkData.h"
#include "FT_config.h"

class FT_Client
{
private:
	
public:
	FT_Client(void);
	~FT_Client(void);

	ClientNetwork* network;
	
	FT_Config ft_config;

	void sendActionPackets();

	char network_data[MAX_PACKET_SIZE];

	void update(double donnees_capteur[6]);

	void get_config();
};