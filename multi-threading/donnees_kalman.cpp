#include <iostream>
#include <vector>
using namespace std;
#include <Eigen/Dense>

#include "kalman.hpp"

void initKalman() {

    cout << "hello" << endl;

    int n = 2;
    int m = 1;
    int c = 2;

    float dt = 0.001;
    double Fobj = 20;

    //initialize Filter
    KalmanFilter kf;
    kf = kf.setRobotKalman(dt, Fobj);

    // List of noisy position measurements (y)
    Eigen::MatrixXd measurements(3,3);
    measurements << 0, 0, 20,
                    0, 0, 22,
                    0, 0, 20;

    measurements = measurements*pow(10,6);

    Eigen::VectorXd y(3);


    // Feed measurements into filter, output estimated states
    float t = 0;
    for(int i = 0; i < measurements.rows(); i++) {
        t += dt;

        y = measurements.block<1,3>(i,0);
        cout << y << endl;
        kf.update(y);

        cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose()
        << ", x_hat[" << i << "] = " << kf.getState().transpose() << endl;
    }
}
