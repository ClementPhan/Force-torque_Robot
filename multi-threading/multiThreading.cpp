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
#include <chrono>

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
    m.lock();
    return rotation;
    m.unlock();
}

Eigen::VectorXd MultiThreading::getMesures(){
    m.lock();
    return mesures;
    m.unlock();
}

Eigen::VectorXd MultiThreading::getDisplacement(){
    m.lock();
    return displacement;
    m.unlock();
}

Eigen::VectorXd MultiThreading::getObjective(){
    m.lock();
    return objective;
    m.unlock();
}

void MultiThreading::setRotation(Eigen::VectorXd rot){
    m.lock();
    rotation = rot;
    m.unlock();
}

void MultiThreading::setMesures(Eigen::VectorXd y){
    m.lock();
    mesures = y;
    m.unlock();
}

void MultiThreading::setDisplacement(Eigen::VectorXd x){
    m.lock();
    displacement = x;
    m.unlock();
}

Eigen::VectorXd MultiThreading::setObjective(Eigen::VectorXd x){
    m.lock();
    return objective;
    m.unlock();
}

void MultiThreading::runKalman(KalmanFilter Kf){
     //cout << "Fobj1" << objective << endl;
    int i =0;
	std::chrono::high_resolution_clock::time_point target_time;
    while(true){
		target_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
        i +=1;
        Kf.update(displacement, mesures, objective, rotation, m);
		{
			std::lock_guard<std::mutex> guard(m);
			cout << "Kalman " << i << endl; 
		}
		std::this_thread::sleep_until(target_time);
    }
}

void MultiThreading::acquireData(){
	//FT_Client* client_capteur;
	//client_capteur = new FT_Client();
	double donnees_capteur[6] = { 0, 0, 0, 0, 0, 0 };
	std::chrono::high_resolution_clock::time_point target_time;
	//client_capteur->get_config();
	int i=0;
    while(true){
		target_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
		i +=1;
		//client_capteur->update(donnees_capteur);
		{
			std::lock_guard<std::mutex> guard(m);
			cout << "Acquisition " << i << endl;
			mesures << donnees_capteur[0], donnees_capteur[1], donnees_capteur[2], donnees_capteur[3], donnees_capteur[4], donnees_capteur[5];
		}
		std::this_thread::sleep_until(target_time);
    }
}

void MultiThreading::sendData(){
    int i = 0;
	std::chrono::high_resolution_clock::time_point target_time;
    while(true){
        i +=1;
		target_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
		sendingScript(); // DO NOT FORGET THE MUTEX !  "std::lock_guard<std::mutex> guard(m);"
		{
			std::lock_guard<std::mutex> guard(m);
			cout << "Sending " << i << endl;
		}
		std::this_thread::sleep_until(target_time);
    }
}
