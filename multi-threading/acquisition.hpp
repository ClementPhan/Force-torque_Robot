//
//  acquisition.hpp
//  main
//
//  Created by Sarah Curtit on 23/03/2018.
//
#pragma once

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>

#include "../tcp_client/ClientNetwork.hpp"
#include "../tcp_client/FT_Client.hpp"
#include "../tcp_client/FT_config.hpp"
#include "../tcp_client/NetworkServices.hpp"
#include "../tcp_client/NetworkData.hpp"


typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned char byte;

#define PORT 49152 /* Port the Net F/T always uses */
#define COMMAND 2 /* Command code 2 starts streaming */
#define NUM_SAMPLES 0 /* Will send infinite sample before stopping */

struct response_struct {
    uint32 rdt_sequence;
    uint32 ft_sequence;
    uint32 status;
    int32 FTData[6];
};

int acquisitionScript(int argc, char ** argv);

