//#include "StdAfx.h"
#include "ClientUDP.h"


ClientUDP::ClientUDP(char* address, char* port) 
{
    // create WSADATA object
    WSADATA wsaData;

    // socket
    ConnectSocket = INVALID_SOCKET;

    // holds address info for socket to connect to
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        exit(1);
    }
    // set address info
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; // For UDP
	hints.ai_protocol = IPPROTO_UDP;  //UDP connection!!!
	
    //resolve server address and port 
	iResult = getaddrinfo(address, port, &hints, &result);

    if( iResult != 0 ) 
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(1);
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);

        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            exit(1);
        }

        // Connect to server.
		iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

        //if (iResult == SOCKET_ERROR)
		if(iResult !=0) // For UDP
        {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            printf ("The server is down... did not connect");
        }
    }



    // no longer need address info for server
    freeaddrinfo(result);



    // if connection failed
    if (ConnectSocket == INVALID_SOCKET) 
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        exit(1);
    }

	
	/*
	// Set the mode of the socket to be nonblocking
    u_long iMode = 1;

    iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
    if (iResult == SOCKET_ERROR)
    {
        printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);        
    }
	*/
}


ClientUDP::ClientUDP(void)
{
	ClientUDP(DEFAULT_ADDRESS_UDP, DEFAULT_PORT_UDP);
}

ClientUDP::~ClientUDP(void)
{
}

int ClientUDP::receivePackets(char * recvbuf) 
{
    iResult = NetworkServices::receiveMessage(ConnectSocket, recvbuf, sizeof(recvbuf));

    if ( iResult == 0 )
    {
        printf("Connection closed\n");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }

    return iResult;
}

int ClientUDP::sendMessage(char * message, int messageSize) 
{
    iResult = NetworkServices::sendMessage(ConnectSocket, message, messageSize);

    if ( iResult == 0 )
    {
        printf("Connection closed\n");
        closesocket(ConnectSocket);
        WSACleanup();
        exit(1);
    }

    return iResult;
}
