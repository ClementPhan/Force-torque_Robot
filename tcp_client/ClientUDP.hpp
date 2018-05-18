#pragma once
// Networking libraries
#include <winsock2.h>
#include <Windows.h>
#include "NetworkServices.hpp"
#include <ws2tcpip.h>
#include <stdio.h> 

// size of our buffer
#define DEFAULT_BUFLEN 512
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientUDP
{
public:

    // ctor/dtor
    ClientUDP(void); // Defaults to "200.200.200.99:49152"
	ClientUDP(char* address, char* port);
    ~ClientUDP(void);

	// for error checking function calls in Winsock library
	int iResult;

	// socket for client to connect to server
	SOCKET ConnectSocket;

	int receivePackets(char *);
	int sendMessage(char * message, int messageSize);
};

