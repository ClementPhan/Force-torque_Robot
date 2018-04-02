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
    /*Eigen::VectorXd rot(3);
    Eigen::VectorXd Fobj(6);
    Eigen::VectorXd y(m);
    Eigen::VectorXd x(n);*/
    
    /*cout << "rot" << rot << endl;
    cout << "y" << y << endl;
    cout << "x" << x << endl;*/
    
    /*rotation = rot;
    objective = Fobj;
    mesures = y;
    displacement = x;*/
    
    Eigen::VectorXd rot(3);
    Eigen::VectorXd Fobj(6);
    Eigen::VectorXd y(6);
    Eigen::VectorXd x(6);
    rot << 0, 0, 0;
    Fobj << 0,0,0,0,0,0;
    y << 0,0,0,0,0,0;
    x << 0,0,0,0,0,0;
    
    rotation = rot;
    mesures = y;
    displacement = x;
    objective = Fobj;
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

void MultiThreading::acquireData(){
    int i =0;
    while(true){
        m.lock();
        i +=1;
        acquisitionScript();
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
