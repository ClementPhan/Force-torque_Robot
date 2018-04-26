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
}


int FT_Client::startStream()
{
	char message[8] = {0};
	*(unsigned __int16*)&message[0] = htons(0x1234); /* standard header. */
	*(unsigned __int16*)&message[2] = htons(0x0002); /* per table 9.1 in Net F/T user manual : start stream */
	*(unsigned __int32*)&message[4] = htonl(0); /* see section 9.1 in Net F/T user manual  : 0 is infinite */
	return NetworkServices::sendMessage(network->ConnectSocket, message, 8);
}

int FT_Client::update(double donnees_capteur[6])
{
	const int responseLength = 36;
	char response[responseLength];
	int iResult = 0;
	while (iResult != responseLength)
	{
		iResult = NetworkServices::receiveMessage(network->ConnectSocket, response, responseLength);
	}

	if (ntohs(*(__int16*)&response[0]) != 0x1234)
	{
		printf( "bad header" );
		return 1;
	}
	for (int i = 0; i < 3; i++) {
		donnees_capteur[i] = ntohl(*(__int32*)&response[12 + i * 4]) / (ft_config.countsPerForce);
	}
	for (int i = 3; i < 6; i++) {
		donnees_capteur[i] = ntohl(*(__int32*)&response[12 + i * 4]) / (ft_config.countsPerTorque);
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
