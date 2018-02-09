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

int main ( int argc, char ** argv ) {
	int socketHandle;			/* Handle to UDP socket used to communicate with Net F/T. */
	struct sockaddr_in addr;	/* Address of Net F/T. */
	struct hostent *he;
  byte request[8];			/* The request data sent to the Net F/T. */
	response_struct resp;				/* The structured response received from the Net F/T. */
	byte response[36];			/* The raw response data received from the Net F/T. */
	int i;						/* Generic loop/array index. */
	int err;					/* Error status of operations. */
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
