//#include "StdAfx.h"
#include "FT_Client.hpp"


FT_Client::FT_Client(void)
{
	network = new ClientUDP(DEFAULT_ADDRESS_UDP, DEFAULT_PORT_UDP);
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
	if (isStreamStarted = false)
	{
		const int messageLength = 8;
		char message[messageLength] = { 0 };
		*(unsigned __int16*)&message[0] = htons(0x1234); /* standard header. */
		*(unsigned __int16*)&message[2] = htons(0x0002); /* per table 9.1 in Net F/T user manual : start stream */
		*(unsigned __int32*)&message[4] = htonl(0); /* see section 9.1 in Net F/T user manual  : 0 is infinite */
		if (NetworkServices::sendMessage(network->ConnectSocket, message, messageLength) < 0)
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
		const int messageLength = 8;
		char message[messageLength] = { 0 };
		*(unsigned __int16*)&message[0] = htons(0x1234); /* standard header. */
		*(unsigned __int16*)&message[2] = htons(0x0000); /* per table 9.1 in Net F/T user manual : stop stream */
		*(unsigned __int32*)&message[4] = htonl(0); /* see section 9.1 in Net F/T user manual  : 0 is infinite */
		if (NetworkServices::sendMessage(network->ConnectSocket, message, messageLength) < 0)
		{
			return 1;
		}
		isStreamStarted = false;
	}
	return 0;
}

int FT_Client::update(int (&donnees_capteur)[6])
{
	const int responseLength = 36;
	char response[responseLength];
	int iResult = 0;

	iResult = NetworkServices::receiveMessage(network->ConnectSocket, response, responseLength);
	if ((iResult < 0) || (iResult != responseLength))
	{
		printf("corrupted message");
		return 1;
	}
	for (int i = 0; i < 6; i++)
	{
		donnees_capteur[i] = ntohl(*(int*)&response[12 + i * 4]);
	}
	return 0;
}
