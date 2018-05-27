#include <iostream>
#include <vector>
using namespace std;
#include <Eigen/Dense>

#include <time.h>
#include <chrono>
#include vector

#include "correcteur.hpp"

using namespace std::chrono;

int main(int argc, char* argv[]) {
    
    
    int n = 2;
    int m = 1;
    int c = 2;
    
    float dt = 0.001;
    double Fobj = 10;

    //initialize Filter
    KalmanFilter kf;
    kf = kf.setRobotKalman(dt, Fobj);
    
    // List of noisy position measurements (y)
    Eigen::MatrixXd measurements(3,3);
    measurements << 20*tan(3.14/3), 0, 20,
                    0, 0, 23,
                    0, 0, 20;
    
    measurements = measurements*pow(10,6);
    
    
    
    
    std::chrono::steady_clock::time_point mesure_begin = std::chrono::steady_clock::now();

    std::cout << "printing out 1000 stars...\n";
    for (int i=0; i<1000; ++i) std::cout << "*";
    std::cout << std::endl;
    
    
    std::chrono::steady_clock::time_point mesure_end = std::chrono::steady_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(mesure_end - mesure_begin);
    
    integral += y*time_span.count();
    
    cout << integral << endl;
    
    
    return 0;
    
    
    /*// Feed measurements into filter, output estimated states
    float t = 0;
    for(int i = 0; i < measurements.rows(); i++) {
        t += dt;
        
        y = measurements.block<1,3>(i,0);
        cout << y << endl;
        kf.update(y);
        
        cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose() << endl 
        << ", x_hat[" << i << "] = " << kf.getState().transpose() << endl;
        cout <<""<<endl;
    }
    
    return 0;*/
}
