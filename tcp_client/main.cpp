//#include "stdafx.h"


#include "FT_Client.h"
#include "Robot_Client.h"


FT_Client* client_capteur;
Robot_Client* client_robot;
int donnees_capteur[6];

int main(int argc, char **argv)
{
	client_capteur = new FT_Client("192.168.1.1","49152");
	//client_robot = new Robot_Client();


	client_capteur->startStream();
	while (true)
	{
		client_capteur->update(donnees_capteur);
		/*
		for (int i = 0; i < 6; i++)
		{
			printf("%f\n", donnees_capteur[i]);
		}
		printf("\n\n");
		Sleep(50);
		*/
	}

}