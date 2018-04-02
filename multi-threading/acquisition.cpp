//
//  acquisition.cpp
//  main
//
//  Created by Sarah Curtit on 23/03/2018.
//

#include "acquisition.hpp"

#include <iostream>
#include <mutex>

using namespace std;


int acquisitionScript(int argc, char ** argv){
    
    int socketHandle;            /* Handle to UDP socket used to communicate with Net F/T. */
    struct sockaddr_in addr;    /* Address of Net F/T. */
    struct hostent *he;
    byte request[8];            /* The request data sent to the Net F/T. */
    response_struct resp;                /* The structured response received from the Net F/T. */
    byte response[36];            /* The raw response data received from the Net F/T. */
    int i;                        /* Generic loop/array index. */
    int err;                    /* Error status of operations. */
    std::string AXES[] = { "Fx", "Fy", "Fz", "Tx", "Ty", "Tz" };
    
    if ( 2 > argc ) /*Check if IP Address */
    {
        std::cout<< "Usage : "<< argv[0] <<" IPADDRESS" <<std::endl;
        return -1;
    }
    
    /* Calculate number of samples, command code, and open socket here. */
    socketHandle = socket(AF_INET, SOCK_DGRAM, 0);
    *(uint16*)&request[0] = htons(0x1234); /* standard header. */
    *(uint16*)&request[2] = htons(COMMAND); /* per table 9.1 in Net F/T user manual. */
    *(uint32*)&request[4] = htonl(NUM_SAMPLES); /* see section 9.1 in Net F/T user manual. */
    
    /* Sending the request. */
    he = gethostbyname(argv[1]);
    memcpy(&addr.sin_addr, he->h_addr_list[0], he->h_length);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    
    std::cout <<"statut de la connection : "<<connect( socketHandle, (struct sockaddr *)&addr, sizeof(addr) )<< std::endl;
    send( socketHandle, request, 8, 0 ); /* sent */
    
    
    /* Receiving 20 responses. */
    for(int j=0; j<20;j++){
        recv( socketHandle, response, 36, 0 );
        resp.rdt_sequence = ntohl(*(uint32*)&response[0]);
        resp.ft_sequence = ntohl(*(uint32*)&response[4]);
        resp.status = ntohl(*(uint32*)&response[8]);
        for( i = 0; i < 6; i++ ) {
            resp.FTData[i] = ntohl(*(int32*)&response[12 + i * 4]);
        }
        
        /* Output the response data. */
        std::cout << "Packet n :" << resp.rdt_sequence<<std::endl;
        std::cout << "Status: 0x" << std::setfill('0') << std::setw(8) << std::hex << resp.status << std::endl;
        for (i =0;i < 6;i++) {
            std::cout<< AXES[i] << " : "<< resp.FTData[i]<<"     ";
        }
        std::cout<<std::endl;
    }
    
    
    
    /* Stop sending. */
    socketHandle = socket(AF_INET, SOCK_DGRAM, 0);
    *(uint16*)&request[0] = htons(0x1234); /* standard header. */
    *(uint16*)&request[2] = htons(0); /* per table 9.1 in Net F/T user manual. 0 to STOP */
    *(uint32*)&request[4] = htonl(NUM_SAMPLES); /* see section 9.1 in Net F/T user manual. */
    
    send( socketHandle, request, 8, 0 ); /* sent */
    
    return 0;
}
