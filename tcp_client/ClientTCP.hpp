#pragma once
// Networking libraries
#include "NetworkServices.hpp"
#include <ws2tcpip.h>
#include <stdio.h> 

// size of our buffer
#define DEFAULT_BUFLEN 512
// port to connect sockets through 
#define DEFAULT_PORT "49151"
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientTCP
{

public:

    // for error checking function calls in Winsock library
    int iResult;

    // socket for client to connect to server
    SOCKET ConnectSocket;

    // ctor/dtor
    ClientTCP(void);
    ~ClientTCP(void);

	int receivePackets(char *);
	int sendMessage(char * message, int messageSize);
};

