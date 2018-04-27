//#include "StdAfx.h"
#include "FT_Client.h"


FT_Client::FT_Client(void)
{
	network = new ClientUDP();
}

FT_Client::FT_Client(char* address, char* port)
{
	network = new ClientUDP(address, port);
}



FT_Client::~FT_Client(void)
{
	stopStream();
}


int FT_Client::startStream()
{
	if(isStreamStarted = false)
	{
		char message[8] = {0};
		*(unsigned __int16*)&message[0] = htons(0x1234); /* standard header. */
		*(unsigned __int16*)&message[2] = htons(0x0002); /* per table 9.1 in Net F/T user manual : start stream */
		*(unsigned __int32*)&message[4] = htonl(0); /* see section 9.1 in Net F/T user manual  : 0 is infinite */
		if (NetworkServices::sendMessage(network->ConnectSocket, message, 8) < 0)
		{
			return 1;
		}
		isStreamStarted = true;
	}
	return 0;
}

int FT_Client::stopStream()
{
	if (isStreamStarted = true)
	{
		char message[8] = { 0 };
			*(unsigned __int16*)&message[0] = htons(0x1234); /* standard header. */
			*(unsigned __int16*)&message[2] = htons(0x0000); /* per table 9.1 in Net F/T user manual : stop stream */
			*(unsigned __int32*)&message[4] = htonl(0); /* see section 9.1 in Net F/T user manual  : 0 is infinite */
			if (NetworkServices::sendMessage(network->ConnectSocket, message, 8) < 0)
			{
				return 1;
			}
			isStreamStarted = false;
	}
	return 0;
}

int FT_Client::update(int donnees_capteur[6])
{
	const int responseLength = 36;
	char response[responseLength];
	int iResult = 0;
	int  temp[6];

	iResult = NetworkServices::receiveMessage(network->ConnectSocket, response, responseLength);
	/*
	if (ntohs(*(__int16*)&response[0]) != 0x1234)
	{
		printf( "bad header" );
		return 1;
	}
	*/
	for (int i = 0; i < 6; i++) {
		//donnees_capteur[i] = ntohl(*(int*)&response[12 + i * 4]);
		temp[i] = ntohl(*(int*)&response[12 + i * 4]);
	}
	for (int i = 0; i < 6; i++)
	{
		printf("%i\n", temp[i]);
	}
	printf("\n\n");
	Sleep(50);
	for (int i = 3; i < 6; i++) {
		//donnees_capteur[i] = ntohl(*(__int32*)&response[12 + i * 4]) / (ft_config.countsPerTorque);
	}
	return 0;


}


void FT_Client::get_config()
{
	const int command_length = 20 ;						/* Commands are always 20 bytes */
	char config_get_command[command_length] = { 0 };	/* readConfig is 1 followed by 19 zeros */
	config_get_command[command_length -1] = 0x1;

	const int response_length = 16 ; /* Response length is specified to be 24 bytes long */
	char config_get_response[response_length];

	int real_response_length = 0;

	while (real_response_length != response_length)
	{
		NetworkServices::sendMessage(network->ConnectSocket, config_get_command, command_length);

		real_response_length = NetworkServices::receiveMessage(network->ConnectSocket, config_get_response, response_length);
	}
}
