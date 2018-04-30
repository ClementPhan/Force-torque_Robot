//#include "stdafx.h"


#include "FT_Client.hpp"
#include "Robot_Client.hpp"


FT_Client* client_capteur;

int donnees_capteur[6];

int main(int argc, char **argv)
{

	char* message;
	std::string s; // Used to convert from int to char*
	s = "1 " + std::to_string(123456) + " #"; // Do not remove the spaces after 1 and before #
	const char* temp = s.c_str();
	message = new char[s.length()];
	memcpy(message, temp, s.length());
	printf(message);
	printf("\n");
	printf("%i", s.length());


	client_capteur = new FT_Client("192.168.1.1","49152");


	client_capteur->startStream();
	while (true)
	{
		client_capteur->update(donnees_capteur);
	}

}