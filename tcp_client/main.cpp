//#include "stdafx.h"


#include "FT_Client.hpp"
#include "Robot_Client.hpp"


FT_Client* client_capteur;

int donnees_capteur[6];

int main(int argc, char **argv)
{
	client_capteur = new FT_Client("192.168.1.1","49152");


	client_capteur->startStream();
	while (true)
	{
		client_capteur->update(donnees_capteur);
	}

}