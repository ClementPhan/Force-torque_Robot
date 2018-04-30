//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include "FT_Client.hpp"
#include "Robot_Client.hpp"


FT_Client* client_capteur;
Robot_Client* robot_client;

int donnees_capteur[6];

int main(int argc, char **argv)
{
	robot_client = new Robot_Client("127.0.0.1", "5000");
	robot_client->sendZandVChange(300000000, 5000000);
	Sleep(10000);
}