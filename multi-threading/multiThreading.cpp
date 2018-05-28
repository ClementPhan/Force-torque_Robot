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



MultiThreading::MultiThreading(){
    int m = 6;
    int n = 6;
    Eigen::VectorXd rot(3);
    Eigen::VectorXd Fobj(6);
    Eigen::VectorXd y(m);
    Eigen::VectorXd x(n);
    Eigen::VectorXd integ(m);
    
    double mC[1000][2];
    for(int i=0; i<2; i++){
        mC[0][i] = 0;
    }
    
    rotation.data = rot;
    objective.data = Fobj;
    mesures.data = y;
    displacement.data = x;
    integral.data = integ.setZero();
    moindreCarres = mC;
}

MultiThreading::MultiThreading(Eigen::VectorXd rot, Eigen::VectorXd y, Eigen::VectorXd x){
    rotation.data = rot;
    mesures.data = y;
    displacement.data = x;
    
    integral.data = y.setZero();
    
    double mC[1000][2];
    for(int i=0; i<2; i++){
        mC[0][i] = 0;
    }
    moindreCarres = mC;
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

Eigen::VectorXd MultiThreading::getIntegral(){
    std::lock_guard<std::mutex> guard(integral.m);
    return integral.data;
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

void MultiThreading::setIntegral(Eigen::VectorXd integ){
    std::lock_guard<std::mutex> guard(integral.m);
    integral.data = integ;
}

void MultiThreading::runKalman(KalmanFilter Kf){
     //cout << "Fobj1" << objective << endl;
    int i =0;
    double a, b;
    double an = 0;
    double ad = 0;
    double tMoy = 0;
    double FzMoy = 0;
    double copie[1000][2];
	std::chrono::high_resolution_clock::time_point target_time;
    while(true){
		target_time = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(10);
        i +=1;
		{
            //on effectue une copie des donnŽes afin de ne pas bloquer le processus pendant le (gros) calcul des coefficients
            moindreCarres.m.lock;
            copie = moindreCarres.data;
            moindreCarres.m.unlock;
            
            // on calcule les moyennes
            for(int j =1; j< copie[0][0]+1; j++){
                FzMoy += copie[j][0];
                tMoy += copie[j][1];
            }
            FzMoy /= copie[0][0];
            tMoy /= copie[0][0];
            
            
            //on effectue le calcul sur la copie
            for(int j =1; j< copie[0][0]+1; j++){
                an+= (copie[j][1]-tMoy)*(copie[j][0]-FzMoy);
                ad+= (copie[j][1]-tMoy)*(copie[j][1]-tMoy);
            }
            a = an/ad;
            b = FMoy - a*tMoy;
            
            kalman_out.data = Kf.update(a, b);
            
			std::lock_guard<std::mutex> guard_2(kalman_out.m);
			/*kalman_out.data = Kf.update(integral.data/0.01);
            integral.data.setZero();*/
		}
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
	int i=0;
    int n=0;
	std::chrono::high_resolution_clock::time_point mesure_begin, mesure_end;
	std::chrono::duration<double> time_span;

	client_capteur->startStream();
    while(true){
		i +=1;
        mesure_begin = std::chrono::high_resolution_clock::now();
		client_capteur->update(donnees_capteur);
		{
			std::lock_guard<std::mutex> guard(m_prompt);
			cout << "Acquisition " << i << endl;
		}
		{
			std::lock_guard<std::mutex> guard(mesures.m);
			mesures.data << donnees_capteur[0], donnees_capteur[1], donnees_capteur[2], donnees_capteur[3], donnees_capteur[4], donnees_capteur[5];
		}
        
        
        mesure_end = std::chrono::high_resolution_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::duration<double> >(mesure_end - mesure_begin);
		{
			//std::lock_guard<std::mutex> guard(integral.m);
            //integral.data += mesures.data * time_span.count();
            std::lock_guard<std::mutex> guard(moindreCarres.m);
            n = moindreCarres[0][0];
            moindreCarres[n+1][0] = sqrt(pow(mesure.data[0], 2) + pow(mesure.data[1], 2) + pow(mesure.data[2], 2));
            moindreCarres[n+1][1] = time_span.count();
            n++;
			
		}
		
    }
}

void MultiThreading::sendData(){

	robot_client = new Robot_Client("192.168.1.99", "5000");
    int i = 0;
	long correction = 0; // Correction avec un gain de 1 000 000
	std::chrono::high_resolution_clock::time_point target_time;
    while(true){
		target_time = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(10);
		i += 1;
		correction += (long) floor(1000000*kalman_out.data);
		if (robot_client->readyToSend())
		{
			robot_client->sendZChange(correction);
		}
		{
			std::lock_guard<std::mutex> guard(m_prompt);
			cout << "Sending " << i << endl;
		}
		std::this_thread::sleep_until(target_time);
    }
}
