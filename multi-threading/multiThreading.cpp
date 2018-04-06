//
//  multiThreading.cpp
//  ALL_BUILD
//
//  Created by Sarah Curtit on 25/03/2018.
//

#include "multiThreading.hpp"

#include <iostream>
#include <stdexcept>
#include <time.h>

using namespace std;


MultiThreading::MultiThreading(){
    int m = 6;
    int n = 6;
    Eigen::VectorXd rot(3);
    Eigen::VectorXd Fobj(6);
    Eigen::VectorXd y(m);
    Eigen::VectorXd x(n);
    
    rotation = rot;
    objective = Fobj;
    mesures = y;
    displacement = x;
    
}

MultiThreading::MultiThreading(Eigen::VectorXd rot, Eigen::VectorXd y, Eigen::VectorXd x){
    rotation = rot;
    mesures = y;
    displacement = x;
}


Eigen::VectorXd MultiThreading::getRotation(){
    return rotation;
}

Eigen::VectorXd MultiThreading::getMesures(){
    return mesures;
}

Eigen::VectorXd MultiThreading::getDisplacement(){
    return displacement;
}

void MultiThreading::setRotation(Eigen::VectorXd rot){
    rotation = rot;
}

void MultiThreading::setMesures(Eigen::VectorXd y){
    mesures = y;
}

void MultiThreading::setDisplacement(Eigen::VectorXd x){
    displacement = x;
}

void MultiThreading::runKalman(KalmanFilter Kf){
     //cout << "Fobj1" << objective << endl;
    int i =0;
    while(true){
        m.lock();
        i +=1;
        displacement = Kf.update(mesures, objective, rotation);
        cout << "Kalman " << i << endl;
        m.unlock();
    }
}

void MultiThreading::acquireData( ){
    
	FT_Client* client_capteur;
	client_capteur = new FT_Client();

	double donnees_capteur[6] = { 0, 0, 0, 0, 0, 0 };

	client_capteur->get_config();
    while(true){
        
        i +=1;
		client_capteur->update(donnees_capteur);
        cout << "Acquisition " << i << endl;
        
		m.lock();
		y << donnees_capteur[0], donnees_capteur[1], donnees_capteur[2], donnees_capteur[3], donnees_capteur[4], donnees_capteur[5];
		m.unlock();
    }
}

void MultiThreading::sendData(){
    int i = 0;
    while(true){
        m.lock();
        i +=1;
        sendingScript();
        cout << "Sending " << i << endl;
        m.unlock();
    }
}
