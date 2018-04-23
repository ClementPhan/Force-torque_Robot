//#include "StdAfx.h"
#include "FT_Client.h"


FT_Client::FT_Client(void)
{

	network = new ClientTCP();

}



FT_Client::~FT_Client(void)
{
}

/*
void FT_Client::sendActionPackets()
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}
*/

int FT_Client::startStream()
{
	char message[8] = {0};
	*(unsigned __int16*)&message[0] = htons(0x1234); /* standard header. */
	*(unsigned __int16*)&message[2] = htons(0x0002); /* per table 9.1 in Net F/T user manual : start stream */
	*(unsigned __int32*)&message[4] = htonl(0); /* see section 9.1 in Net F/T user manual  : 0 is infinite */
	return NetworkServices::sendMessage(network->ConnectSocket, message, 8);
}

void FT_Client::updateUDP(double donnees_capteur[6])
{
	const int responseLength = 36;
	char response[responseLength];
	NetworkServices::receiveMessage(network->ConnectSocket, response, responseLength);
}

void FT_Client::update(double donnees_capteur[6])
{
	const int command_length = 20;						/* Commands are always 20 bytes */
	char FT_get_command[command_length] = { 0 };	/* ReadFT is 0 followed by 19 zeros */

	const int response_length = 16; /* Response length is specified to be 16 bytes long */
	char FT_get_response[response_length];

	int real_response_length = 0;

	while (real_response_length != response_length)
	{
		NetworkServices::sendMessage(network->ConnectSocket, FT_get_command, command_length);

		real_response_length = NetworkServices::receiveMessage(network->ConnectSocket, FT_get_response, response_length);
	}
	for (int i = 0; i < 6; i++)
	{
		donnees_capteur[i] = ntohs(*(unsigned __int16 *)&FT_get_response[2*i]);
	}

	for (int i = 0; i < 3; i++)
	{
		donnees_capteur[i] = donnees_capteur[i] * ft_config.scaleFactors[i] / ft_config.countsPerForce;
		donnees_capteur[i+3] = donnees_capteur[i+3] * ft_config.scaleFactors[i+3] / ft_config.countsPerTorque;
	}
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

	unsigned __int16 plop1,	plop2, plop3, plop4, plop5, plop6, plop7, plop8;

	plop1 = ntohs(*(unsigned __int16 *)&config_get_response[0]);
	plop2 = ntohs(*(unsigned __int16 *)&config_get_response[2]);
	plop3 = ntohs(*(unsigned __int16 *)&config_get_response[4]);
	plop4 = ntohs(*(unsigned __int16 *)&config_get_response[6]);
	plop5 = ntohs(*(unsigned __int16 *)&config_get_response[8]);
	plop6 = ntohs(*(unsigned __int16 *)&config_get_response[10]);
	plop7 = ntohs(*(unsigned __int16 *)&config_get_response[12]);
	plop8 = ntohs(*(unsigned __int16 *)&config_get_response[14]);

	printf("plop1 = %#x\n\n", plop1);
	printf("plop2 = %#x\n\n", plop2);
	printf("plop3 = %#x\n\n", plop3);
	printf("plop4 = %#x\n\n", plop4);
	printf("plop5 = %#x\n\n", plop5);
	printf("plop6 = %#x\n\n", plop6);
	printf("plop7 = %#x\n\n", plop7);
	printf("plop8 = %#x\n\n", plop8);
	


	
	unsigned char temp[16]; 
	std::memcpy(temp, config_get_response, 16);
	printf("Header\n");
	printf("%#x", temp[0]);
	printf("%x", temp[1]);	printf("\n\n");

	printf("Force units\n");
	printf("%x", temp[2]);	printf("\n\n");

	printf("Torque units\n");
	printf("%x", temp[3]); printf("\n\n");

	printf("Counts per Force\n");
	printf("%x", temp[4]);
	printf("%x", temp[5]);
	printf("%x", temp[6]);
	printf("%x", temp[7]); printf("\n\n");

	printf("Counts per Torque\n");
	printf("%x", temp[8]);
	printf("%x", temp[9]);
	printf("%x", temp[10]);
	printf("%x", temp[11]); printf("\n\n");

	printf("Force units\n");
	printf("%x", temp[12]);
	printf("%x", temp[13]);
	printf("%x", temp[14]);
	printf("%x", temp[15]);


	std::memcpy(&ft_config.countsPerForce,	temp + 4, 4); /* Copy of output as specified in the ATI manual */
	std::memcpy(&ft_config.countsPerTorque,	temp + 8, 4);
	std::memcpy(ft_config.scaleFactors,		temp + 12, 12);
}
