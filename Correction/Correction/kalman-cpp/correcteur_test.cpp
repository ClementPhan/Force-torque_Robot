#include <iostream>
#include <vector>
using namespace std;
#include <Eigen/Dense>

#include "correcteur.hpp"

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
    
    Eigen::VectorXd y;
    
    
    vector<Eigen::VectorXd> integral(1000);
    
    int i = 1;
    int j =0;
    while(i<= 880){
        j++;
        integral[0] << j, 0, 0, 0, 0, 0;
        integral[i] << 1, 0, 0, 0, 0, 0;
        i++;
    }
    
    Eigen::VectorXd somme;
    somme << 0, 0, 0, 0, 0, 0;
    for(int k = 0; k < integral[0][1]; k++){
        somme += integral[4];
    }
    
    cout << somme[1] << endl;
    
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
