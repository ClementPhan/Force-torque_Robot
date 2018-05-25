//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include "FT_Client.hpp"
#include "Robot_Client.hpp"


FT_Client* client_capteur;
Robot_Client* robot_client;

int donnees_capteur[6];

int main(int argc, char **argv)
{
	robot_client = new Robot_Client("192.168.1.99", "5000");
	Sleep(1000);
	
	int i = 0;
	while (i < 10)
	{
		
		if (robot_client->readyToSend())
		{
			robot_client->sendZChange( i );
			printf("sent\n");
			i++;
		}
		
	}
	while (true)
	{
		printf("wait");
	}

	
	Sleep(10000);
}