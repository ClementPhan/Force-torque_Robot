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


MultiThreading::MultiThreading(){}

/*MultiThreading::MultiThreading(){
    int m = 6;
    int n = 6;
    Eigen::VectorXd rot(3);
    Eigen::VectorXd y(m);
    Eigen::VectorXd x(n);
    
    rotation = rot;
    mesures = y;
    displacement = x;
}*/


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

