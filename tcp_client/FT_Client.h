#pragma once
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
#include "ClientUDP.h"
#include "FT_config.h"

class FT_Client
{
private:
	
public:
	FT_Client(void);
	~FT_Client(void);

	ClientUDP* network;
	
	FT_Config ft_config;

	int startStream();

	int update(double donnees_capteur[6]);

	void update_old(double donnees_capteur[6]);

	void get_config();
};