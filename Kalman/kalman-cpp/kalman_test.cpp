#include <iostream>
#include <vector>
using namespace std;
#include <Eigen/Dense>

#include "kalman.hpp"

int main(int argc, char* argv[]) {

    
    // Construct the filter
    KalmanFilter kf(dt, A, C, W, V, P);
    
    // List of noisy position measurements (y)
    vector<double> measurements(10, 1);

    
    // Best guess of initial states
    Eigen::VectorXd x0(n);
    x0 << measurements[0], 0, -9.81;
    kf.init(0, x0);
    
    // Feed measurements into filter, output estimated states
    double t = 0;
    Eigen::VectorXd y(m);
    cout << "t = " << t << ", " << "x_hat[0]: " << kf.state().transpose() << endl;
    Eigen::VectorXd Fobj(m);
    for(int i = 0; i < measurements.size(); i++) {
        
        t += dt;
        double theta = 0; //rotation entre l'état précédent et l'état actuel
        
        A << 1, 0, 0, dt, 0, 0,
        0, 1, 0, 0, dt, 0,
        0, 0, 1, 0, 0, dt,
        0, 0, 0, cos(theta), -sin(theta), 0,
        0, 0, 0, sin(theta), cos(theta), 0,
        0, 0, 0, 0, 0, 1;
        
        y << measurements[i];
        kf.update(y, Fobj);
        cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose()
        << ", x_hat[" << i << "] = " << kf.state().transpose() << endl;
    }
    
    return 0;
}
