#pragma once
#include <cstring>
#include "Network_Core/ClientUDP.hpp"

/*
*	PURPOSE :
*	connecting to an ATI FT sensor
*
*	USE :
*	Create the class object with correct address and port (by default
*	is 192.168.1.1:49152)
*
*	Then start the stream with startStream(), can be stopped at any time
*	with stopStream(), resumed... It is automaticly stopped at destruction.
*
*	Update data with update(int) only when stream is started.
*
*
*/

// address ot connect through
#define DEFAULT_ADDRESS_UDP "192.168.1.1"
// port to connect sockets through
#define DEFAULT_PORT_UDP "49152"

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

	int update(int (&donnees_capteur)[6]);
};