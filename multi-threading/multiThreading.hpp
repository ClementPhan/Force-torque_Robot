//
//  multiThreading.hpp
//  ALL_BUILD
//
//  Created by Sarah Curtit on 25/03/2018.
//

#include <Eigen/Dense>
#include <mutex>

using namespace std;

#pragma once

class MultiThreading{
    
    public:
    
        // Constructor
        MultiThreading(Eigen::VectorXd rot, Eigen::VectorXd y, Eigen::VectorXd x);
    
        //Create blank estimator
        MultiThreading();
    
        // Accessors
        Eigen::VectorXd getRotation();
        Eigen::VectorXd getMesures();
        Eigen::VectorXd getDisplacement();
    
        // Modifiers
        void setRotation(Eigen::VectorXd rot);
        void setMesures(Eigen::VectorXd y);
        void setDisplacement(Eigen::VectorXd x);

    private:
    
        //shared variables
        Eigen::VectorXd rotation;
        Eigen::VectorXd mesures;
        Eigen::VectorXd displacement;
        mutex acquisition;
        mutex posting;
};

