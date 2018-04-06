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
    client_capteur = new FT_Client();
    
    client_capteur->update();
    printf("counts per force : %x\n", client_capteur->ft_config.countsPerForce);
    printf("counts per torque : %x\n", client_capteur->ft_config.countsPerTorque);
    printf("done\n");
}
