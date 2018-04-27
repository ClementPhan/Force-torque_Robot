#pragma once
// Networking libraries
#include <winsock2.h>
#include <Windows.h>
#include "NetworkServices.h"
#include <ws2tcpip.h>
#include <stdio.h> 

// size of our buffer
#define DEFAULT_BUFLEN 512
// address ot connect through
#define DEFAULT_ADDRESS_UDP "200.200.200.99"
// port to connect sockets through
#define DEFAULT_PORT_UDP "49152"
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientUDP
{

public:

    // for error checking function calls in Winsock library
    int iResult;

    // socket for client to connect to server
    SOCKET ConnectSocket;

    // ctor/dtor
    ClientUDP(void);
	ClientUDP(char* address, char* port);
    ~ClientUDP(void);

	int receivePackets(char *);
	int sendMessage(char * message, int messageSize);
};

