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
    
    rotation.data = rot;
    objective.data = Fobj;
    mesures.data = y;
    displacement.data = x;
	correction.data = 0;
    
}

MultiThreading::MultiThreading(Eigen::VectorXd rot, Eigen::VectorXd y, Eigen::VectorXd x){
    rotation.data = rot;
    mesures.data = y;
    displacement.data = x;
	correction.data = 0;
}


Eigen::VectorXd MultiThreading::getRotation(){
	std::lock_guard<std::mutex> guard(rotation.m);
    return rotation.data;
}

Eigen::VectorXd MultiThreading::getMesures(){
	std::lock_guard<std::mutex> guard(mesures.m);
    return mesures.data;
}

Eigen::VectorXd MultiThreading::getDisplacement(){
	std::lock_guard<std::mutex> guard(displacement.m);
    return displacement.data;
}

Eigen::VectorXd MultiThreading::getObjective(){
	std::lock_guard<std::mutex> guard(objective.m);
    return objective.data;
}

void MultiThreading::setRotation(Eigen::VectorXd rot){
	std::lock_guard<std::mutex> guard(rotation.m);
    rotation.data = rot;
}

void MultiThreading::setMesures(Eigen::VectorXd y){
	std::lock_guard<std::mutex> guard(mesures.m);
    mesures.data = y;
}

void MultiThreading::setDisplacement(Eigen::VectorXd x){
	std::lock_guard<std::mutex> guard(displacement.m);
    displacement.data = x;
}

void MultiThreading::setObjective(Eigen::VectorXd Fobj){
	std::lock_guard<std::mutex> guard(objective.m);
    objective.data = Fobj;
}

void MultiThreading::runKalman(KalmanFilter Kf){
     //cout << "Fobj1" << objective << endl;
    int i =0;
	std::chrono::high_resolution_clock::time_point target_time;
    while(true){
		target_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
        i +=1;
        correction.data = Kf.update(mesures.data);
		{
			std::lock_guard<std::mutex> guard(m_prompt);
			cout << "Kalman " << i << endl; 
		}
		std::this_thread::sleep_until(target_time);
    }
}

void MultiThreading::acquireData(){
	client_capteur = new FT_Client();
	int donnees_capteur[6] = { 0, 0, 0, 0, 0, 0 };  // Données avec un gain de 1 000 000
	std::chrono::high_resolution_clock::time_point target_time;
	int i=0;
    while(true){
		target_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
		i +=1;
		client_capteur->update(donnees_capteur);
		{
			std::lock_guard<std::mutex> guard(m_prompt);
			cout << "Acquisition " << i << endl;
		}
		{
			std::lock_guard<std::mutex> guard(mesures.m);
			mesures.data << donnees_capteur[0], donnees_capteur[1], donnees_capteur[2], donnees_capteur[3], donnees_capteur[4], donnees_capteur[5];
		}
		std::this_thread::sleep_until(target_time);
    }
}

void MultiThreading::sendData(){

	robot_client = new Robot_Client("192.168.1.99", "5000");
    int i = 0;
	std::chrono::high_resolution_clock::time_point target_time;
    while(true){
        i +=1;
		target_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(10);
		if (robot_client->readyToSend())
		{
			std::lock_guard<std::mutex> guard(correction.m);
			robot_client->sendZChange(correction.data);
		}
		{
			std::lock_guard<std::mutex> guard(m_prompt);
			cout << "Sending " << i << endl;
		}
		std::this_thread::sleep_until(target_time);
    }
}
