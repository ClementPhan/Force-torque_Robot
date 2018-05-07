#pragma once
// Networking libraries
#include "NetworkServices.hpp"
#include <ws2tcpip.h>
#include <stdio.h> 

// size of our buffer
#define DEFAULT_BUFLEN 512
// port to connect sockets through 
#define DEFAULT_PORT_TCP "49151"
#define DEFAULT_ADDRESS_TCP "200.200.200.99"
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
	ClientTCP(const char * address, const char * port);
    ~ClientTCP(void);

	int recvMessage(char * recvbuf, int buflen);
	int sendMessage(char * message, int messageSize);
	int sendMessage(const char * message, int messageSize);
};

