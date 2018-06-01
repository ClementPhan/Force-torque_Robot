#include <thread>
#include <iostream>

#include "multiThreading.hpp"

using namespace std;

// Run the Kalman filter every dt
void runLoop1(MultiThreading a){
    
}

void runLoop2(KalmanFilter a){
    
}

int main(int argc, char ** argv) {

    double dt = 1.0/30.0;
	double forceObj = 5; // 5 newtons
    
    
    // Initializing the Kalman filter characteristics
    KalmanFilter Kf;
    Kf = Kf.setRobotKalman(dt, forceObj);

    // Initializing global variables
    MultiThreading global;
    
    

    thread Kalman(&MultiThreading::runKalman , &global, Kf);
    thread getInfo(&MultiThreading::acquireData, &global);
    thread sendInfo(&MultiThreading::sendData, &global);
    
    
    getInfo.detach();
    sendInfo.detach();
    Kalman.join();
    
    // We launch the processus and will run Kalman every dt 
    clock_t t0;
    t0 = clock(); // initial time
	
}


