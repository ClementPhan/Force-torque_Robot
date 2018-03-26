#include <thread>
#include <iostream>

#include "kalman.hpp"
#include "acquisition.hpp"
#include "envoi.hpp"
#include "multiThreading.hpp"

using namespace std;

// Run the Kalman filter every dt
void runLoop1(MultiThreading a){
    
}

void runLoop2(KalmanFilter a){
    
}

int main(int argc, char* argv[]) {

    double dt = 1.0/30.0;
    
    // Initializing global variables
    MultiThreading global;
    
    // Initializing the Kalman filter characteristics
    KalmanFilter Kf;
    /*Kf = Kf.setRobotKalman(dt);*/

    //thread Kalman(runLoop1, global);
    //thread Kalman(runLoop2, Kf);

    //Kalman.join();
    
    // We launch the processus and will run Kalman every dt 
    clock_t t0;
    t0 = clock(); // initial time
    
    
    
    cout<<"All threads joined\n" << endl;
}


