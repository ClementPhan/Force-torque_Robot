//#include "StdAfx.h"
#include "FT_Client.h"


FT_Client::FT_Client(void)
{

	network = new ClientNetwork();

	// send init packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}


FT_Client::~FT_Client(void)
{
}

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

void FT_Client::update(double donnees_capteur[6])
{
	Packet packet;
	int data_length = network->receivePackets(network_data);

	if (data_length <= 0)
	{
		//no data recieved
		return;
	}

	int i = 0;
	while (i < (unsigned int)data_length)
	{
		packet.deserialize(&(network_data[i]));
		i += sizeof(Packet);

		switch (packet.packet_type) {

		case ACTION_EVENT:

			printf("client received action event packet from server\n");

			sendActionPackets();

			break;

		default:

			printf("error in packet types\n");

			break;
		}
	}
}

void FT_Client::get_config()
{
	const int command_length = 20 ;						/* Commands are always 20 bytes */
	char config_get_command[command_length] = { 1 };	/* readConfig is 1 followed by 19 zeros */

	const int response_length = 16 ; /* Respose length is specified to be 24 bytes long */
	char config_get_response[response_length];

	int real_response_length = 0;

	while (real_response_length != response_length)
	{
		NetworkServices::sendMessage(network->ConnectSocket, config_get_command, command_length);

		real_response_length = NetworkServices::receiveMessage(network->ConnectSocket, config_get_response, response_length);
	}

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
