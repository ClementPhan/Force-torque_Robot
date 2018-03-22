/**
 * Test for the KalmanFilter class with 1D projectile motion.
 *
 * @author: Hayk Martirosyan
 * @date: 2014.11.15
 */

#include <iostream>
#include <vector>
using namespace std;
#include <Eigen/Dense>

#include "kalman.hpp"

int main(int argc, char* argv[]) {
    
    int n = 6; // Number of states
    int m = 3; // Number of measurements
    
    //outputs: (x, y, z, u, v, w) where values are increments !! not absolute values
    
    
    int k = 1; // V aideur du V essort
    
    double dt = 1.0/30; // Time step
    
    Eigen::MatrixXd A(n, n); // System dynamics matrix
    Eigen::MatrixXd C(m, n); // Output matrix
    Eigen::MatrixXd W(n, n); // Process noise covariance
    Eigen::MatrixXd V (m, m); // Measurement noise covariance
    Eigen::MatrixXd P(n, n); // Estimate error covariance
    
    // Discrete LTI projectile motion, measuring position only
    A << 1, 0, 0, dt, 0, 0,
    0, 1, 0, 0, dt, 0,
    0, 0, 1, 0, 0, dt,
    0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 1;
    
    C << 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 1/(dt*k);
    
    // Reasonable covariance matrices
    /* W << .05, .05, .0, .05, .05, .0, .0, .0, .0;
     V  << 5;
     P << .1, .1, .1, .1, 10000, 10, .1, 10, 100;*/
    
    Eigen::MatrixXd ligne(1,4);
    ligne << pow(10,-4), pow(10,-4), pow(10,-4), pow(10,-4);
    
    W << ligne, ligne, ligne, ligne, ligne, ligne;
    
    int Fx = 1;
    int Fy = 1;
    int Fz = 10;
    
    V << 1*Fx*Fx, 1.25*Fx*Fy, 0.75*Fx*Fz,
    1.25*Fx*Fz, 1.25*1.25*Fy*Fy, 0.75*1.25*Fy*Fz,
    0.75*Fx*Fz, 0.75*1.25*Fy*Fz, 0.75*0.75*Fz*Fz;
    V = V*pow(10, -4);
    
    P = W;
    
    cout << "A: \n" << A << endl;
    cout << "B: \n" << C << endl;
    cout << " W: \n" <<  W << endl;
    cout << "R: \n" << V  << endl;
    cout << "P: \n" << P << endl;
    
    // Construct the filter
    KalmanFilter kf(dt, A, C, W, V, P);
    
    // List of noisy position measurements (y)
    vector<double> measurements(10, 1);
    /*1.04202710058, 1.10726790452, 1.2913511148, 1.48485250951, 1.72825901034,
     1.74216489744, 2.11672039768, 2.14529225112, 2.16029641405, 2.21269371128,
     2.57709350237, 2.6682215744, 2.51641839428, 2.76034056782, 2.88131780617,
     2.88373786518, 2.9448468727, 2.82866600131, 3.0006601946, 3.12920591669,
     2.858361783, 2.83808170354, 2.68975330958, 2.66533185589, 2.81613499531,
     2.81003612051, 2.88321849354, 2.69789264832, 2.4342229249, 2.23464791825,
     2.30278776224, 2.02069770395, 1.94393985809, 1.82498398739, 1.52526230354,
     1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913, 0.678547664519,
     0.562381751596, 0.355468474885, -0.155607486619, -0.287198661013, -0.602973173813*/
    
    
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
        y << measurements[i];
        kf.update(y, Fobj);
        cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose()
        << ", x_hat[" << i << "] = " << kf.state().transpose() << endl;
    }
    
    return 0;
}
