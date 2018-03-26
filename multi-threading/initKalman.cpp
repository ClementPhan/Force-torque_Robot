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


    
Eigen::VectorXd runFilter(){
    
    
    // Feed measurements into filter, output estimated states
    double t = 0;

    /*cout << "t = " << t << ", " << "x_hat[0]: " << kf.state().transpose() << endl;
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
    }*/
}
    

    
    








