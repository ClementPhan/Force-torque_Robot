//
//  multiThreading.hpp
//  ALL_BUILD
//
//  Created by Sarah Curtit on 25/03/2018.
//

#include <Eigen/Dense>
#include <mutex>

#include "kalman.hpp"
#include "acquisition.hpp"
#include "sending.hpp"

using namespace std;

#pragma once

class MultiThreading{
private:
    
//shared variables
Eigen::VectorXd rotation;
Eigen::VectorXd mesures;
Eigen::VectorXd displacement;
Eigen::VectorXd objective;
mutex m;
    
public:

    // Constructor
    MultiThreading(Eigen::VectorXd rot, Eigen::VectorXd y, Eigen::VectorXd x);

    //Create blank estimator
    MultiThreading();

    // Accessors
    Eigen::VectorXd getRotation();
    Eigen::VectorXd getMesures();
    Eigen::VectorXd getDisplacement();
    Eigen::VectorXd getObjective();

    // Modifiers
    void setRotation(Eigen::VectorXd rot);
    void setMesures(Eigen::VectorXd y);
    void setDisplacement(Eigen::VectorXd x);
    void setObjective(Eigen::VectorXd Fobj);

    //loop functions
    void runKalman(KalmanFilter Kf);
    void acquireData();
    void sendData();
};

