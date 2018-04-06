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

void MultiThreading::acquireData(int argc, char ** argv ){
    int i =0;
    while(true){
        m.lock();
        i +=1;
        acquisitionScript(argc, argv);
        cout << "Acquisition " << i << endl;
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
