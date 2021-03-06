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
    

    rotation.data = rot;
    objective.data = Fobj;
    mesures.data = y;
    displacement.data = x;
    integral.data = integ.setZero();

	for (int i = 0; i<2; i++) {
		moindreCarres.data.mCx[0][i] = 0;
	}
}

MultiThreading::MultiThreading(Eigen::VectorXd rot, Eigen::VectorXd y, Eigen::VectorXd x){
    rotation.data = rot;
    mesures.data = y;
    displacement.data = x;
    
    integral.data = y.setZero();
    
    for(int i=0; i<2; i++){
		moindreCarres.data.mCx[0][i] = 0;
    }
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
    double ax, ay, az, bx, by, bz;
    double an = 0;
    double ad = 0;
    double tMoy = 0;
    double FxMoy = 0;
	double FyMoy = 0;
	double FzMoy = 0;
    double copiex[10000][2];
	double copiey[10000][2];
	double copiez[10000][2];
	std::chrono::high_resolution_clock::time_point target_time;
    while(true){
		target_time = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(10);
        i +=1;
		{
            //on effectue une copie des donn�es afin de ne pas bloquer le processus pendant le (gros) calcul des coefficients
			{
				std::lock_guard<std::mutex> guard(moindreCarres.m);
				memcpy(copiex, moindreCarres.data.mCx, sizeof(moindreCarres.data.mCx));
                memcpy(copiey, moindreCarres.data.mCy, sizeof(moindreCarres.data.mCy));
                memcpy(copiez, moindreCarres.data.mCz, sizeof(moindreCarres.data.mCz));
                
				moindreCarres.data.mCx[0][0] = 0;
                moindreCarres.data.mCy[0][0] = 0;
                moindreCarres.data.mCz[0][0] = 0;
			}
            
            /////////////////////
            // on calcule les moyennes
            for(int j =1; j< copiex[0][0]+1; j++){
                FxMoy += copiex[j][0];
                tMoy += copiex[j][1];
            }
            FxMoy /= copiex[0][0];
            tMoy /= copiex[0][0];
            
            
            //on effectue le calcul sur la copie
            for(int j =1; j< copiex[0][0]+1; j++){
                an+= (copiex[j][1]-tMoy)*(copiex[j][0]-FxMoy);
                ad+= (copiex[j][1]-tMoy)*(copiex[j][1]-tMoy);
            }
            ax = an/ad;
            bx = FxMoy - ax*tMoy;
            FxMoy = bx + ax*0.1/2;

			//on r�initialise
			an = 0;
			ad = 0;
			FxMoy = 0;
			tMoy = 0;
            
            
            /////////////////
            for(int j =1; j< copiey[0][0]+1; j++){
                FyMoy += copiey[j][0];
            }
            FyMoy /= copiey[0][0];
            
            
            //on effectue le calcul sur la copie
            for(int j =1; j< copiey[0][0]+1; j++){
                an+= (copiey[j][1]-tMoy)*(copiey[j][0]-FzMoy);
                ad+= (copiey[j][1]-tMoy)*(copiey[j][1]-tMoy);
            }
            ay = an/ad;
            by = FyMoy - ay*tMoy;
            
            FyMoy = by+0.1*ay/2;
            
            
            //on r�initialise
            an = 0;
            ad = 0;
            FyMoy = 0;
            tMoy = 0;
            
            
            //////////////////////////
            for(int j =1; j< copiez[0][0]+1; j++){
                FzMoy += copiez[j][0];
            }
            FzMoy /= copiez[0][0];
            
            
            //on effectue le calcul sur la copie
            for(int j =1; j< copiez[0][0]+1; j++){
                an+= (copiez[j][1]-tMoy)*(copiez[j][0]-FzMoy);
                ad+= (copiez[j][1]-tMoy)*(copiez[j][1]-tMoy);
            }
            az = an/ad;
            bz = FzMoy - az*tMoy;
            FzMoy = bz+az*0.1/2;
            
            //on r�initialise
            an = 0;
            ad = 0;
            FzMoy = 0;
            tMoy = 0;

            
			{
				std::lock_guard<std::mutex> guard_2(kalman_out.m);
				kalman_out.data = Kf.update(az, bz);
			}
		}
		if((i%50)==0)
		{
			std::lock_guard<std::mutex> guard(m_prompt);
			std::lock_guard<std::mutex> guard2(kalman_out.m);
			cout << "Kalman " << kalman_out.data *1000 << endl; 
		}
		std::this_thread::sleep_until(target_time);
    }
}

void MultiThreading::acquireData(){
	client_capteur = new FT_Client("192.168.1.1","49152");
	int donnees_capteur[6] = { 0, 0, 0, 0, 0, 0 };  // Donn�es avec un gain de 1 000 000
	int i=0;
    int n=0;
	std::chrono::high_resolution_clock::time_point mesure_begin, mesure_end;
	std::chrono::duration<double> time_span;

	client_capteur->startStream();
    while(true){
		i +=1;
        mesure_begin = std::chrono::high_resolution_clock::now();
		client_capteur->update(donnees_capteur);
		if ((i%10000)==0)
		{
			std::lock_guard<std::mutex> guard(m_prompt);
			//cout << "Acquisition " << donnees_capteur[2] << endl;
		}
		{
			std::lock_guard<std::mutex> guard(mesures.m);
			mesures.data << donnees_capteur[0], donnees_capteur[1], donnees_capteur[2], donnees_capteur[3], donnees_capteur[4], donnees_capteur[5];
		}
        
        
        mesure_end = std::chrono::high_resolution_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::duration<double> >(mesure_end - mesure_begin);
		{
            std::lock_guard<std::mutex> guard(moindreCarres.m);

            n = lround(moindreCarres.data.mCx[0][0]);
            
            moindreCarres.data.mCx[n+1][0] = mesures.data[0];
            moindreCarres.data.mCy[n+1][0] = mesures.data[1];
            moindreCarres.data.mCz[n+1][0] = mesures.data[2];
            
            moindreCarres.data.mCx[n+1][1] = time_span.count();
            moindreCarres.data.mCy[n+1][1] = time_span.count();
            moindreCarres.data.mCz[n+1][1] = time_span.count();
            n++;
			
			moindreCarres.data.mCx[0][0] = n;
			moindreCarres.data.mCy[0][0] = n;
            moindreCarres.data.mCz[0][0] = n;
		}
		
    }
}

void MultiThreading::sendData(){

	robot_client = new Robot_Client("192.168.1.101", "5000");
    int i = 0;
	int ForceMax = 20;
	long correction = 0; // Correction avec un gain de 1 000 000
	std::chrono::high_resolution_clock::time_point target_time;
	double kalmanData[101] = { 0 };
	bool approachIsOver = false;


	std::this_thread::sleep_for(50ms);
    while(true){
		target_time = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(10); //
		i += 1;
		{
			std::lock_guard<std::mutex> guard(kalman_out.m);
			kalmanData[0]+=1;
			kalmanData[lround(kalmanData[0])] = kalman_out.data;
		}
		
		if (robot_client->readyToSend())
		{
			{
				std::lock_guard<std::mutex> guard(mesures.m);
				if (pow((mesures.data[0] / 1000000.0), 2) + pow((mesures.data[1] / 1000000.0), 2) > pow(ForceMax, 2))
				{
					robot_client->sendSTOP();
				}
			}

			correction += lround(winsorize(kalmanData)*1000000000);  //Correction is in mm, kalman is in m, gain is 1M
			kalmanData[0] = 0;
			robot_client->sendZChange(correction);
			{
				std::lock_guard<std::mutex> guard(m_prompt);
				cout << "Sending " << correction << endl;
			}
		}
		
		std::this_thread::sleep_until(target_time);
    }
}

double MultiThreading::winsorize(double* data){

    double V = 0;
    double mean = 0;
    double N = data[0];
    for(int i=1; i< N+1; i++){
        mean += data[i];
        V += data[i]*data[i];
    }

    mean /= N;
    V = V/N-mean*mean;
    double Ec = sqrt(V);
    
	double newMean = 0;
	int count = 0;
    for(int i=1; i < N+1; i++){
		if ((data[i] <= mean + Ec*10 ) && (data[i] >= mean - Ec*10 ))
		{
			newMean += data[i];
			count++;
		}
    }

	newMean /= count;
	return newMean; 
};

