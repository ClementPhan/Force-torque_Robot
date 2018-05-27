//
//  multiThreading.hpp
//  ALL_BUILD
//
//  Created by Sarah Curtit on 25/03/2018.
//

#pragma once

#include <Eigen/Dense>
#include <mutex>

#include "../Correction/Correction/kalman-cpp/correcteur.hpp"
#include "sending.hpp"
#include "../tcp_client/FT_Client.hpp"
#include "../tcp_client/Robot_Client.hpp"
#include <vector>

using namespace std;


template <typename T>
struct shared_data{
	mutex m;
	T data;
};



class MultiThreading{
private:

	// Networking

	Robot_Client * robot_client;
	FT_Client* client_capteur;
    
	// Shared variables
	shared_data<Eigen::VectorXd> rotation;
	shared_data<Eigen::VectorXd> mesures;
	shared_data<Eigen::VectorXd> displacement;
	shared_data<Eigen::VectorXd> objective;
    shared_data<Eigen::VectorXd> integral;
    
    shared_data<vector< vector<double> > > moindreCarrés;

	shared_data<double> kalman_out;

	// Other mutexes
	mutex m_prompt; // For cout or other prompt actions
    
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
    Eigen::VectorXd getIntegral();

    // Modifiers
    void setRotation(Eigen::VectorXd rot);
    void setMesures(Eigen::VectorXd y);
    void setDisplacement(Eigen::VectorXd x);
    void setObjective(Eigen::VectorXd Fobj);
    void setIntegral(Eigen::VectorXd integ);

    //loop functions
    void runKalman(KalmanFilter Kf);
    void acquireData();
    void sendData();
};

