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

void initKalman() {
    
    int n = 6; // Nombre d'états: 3 déplacements et 3 vitesses
    int m = 3; // Nombre de mesures: les forces mesurées dans les trois directions par le capteur (repère de la surface)
    //outputs: (x, y, z, u, v, w) les déplacements sont relatifs à la trajectoire, les vitesses sont absolues
    
    
    int k = 1; // Raideur du ressort
    
    double dt = 1.0/30; // Time step
    
    Eigen::MatrixXd A(n, n); // comportement du system
    Eigen::MatrixXd C(m, n); // relation entre les mesures et le vecteur d'état
    Eigen::MatrixXd W(n, n); // Matrice de covariance du bruit lié au processus
    Eigen::MatrixXd V (m, m); // Matrice de covariance du bruit de mesure
    Eigen::MatrixXd P(n, n); // Matrice de covariance de l'erreur
    
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
    0, 0, k*dt;  // DeltaF = kDeltax = kv*dt
    
    Eigen::MatrixXd ligne(1,4);
    ligne << pow(10,-4), pow(10,-4), pow(10,-4), pow(10,-4); // précision du déplacement du robot
    
    W << ligne, ligne, ligne, ligne, ligne, ligne;
    
    int Fx = 1;
    int Fy = 1;
    int Fz = 10; // ordres de grandeurs des forces que l'on s'attend à rencontrer afin d'en déduire le bruit du capteur
    
    V << 1*Fx*Fx, 1.25*Fx*Fy, 0.75*Fx*Fz,
    1.25*Fx*Fz, 1.25*1.25*Fy*Fy, 0.75*1.25*Fy*Fz,
    0.75*Fx*Fz, 0.75*1.25*Fy*Fz, 0.75*0.75*Fz*Fz; //Les valeurs sont les valeurs de précision de la mesure indiquées sur le certificat d'échantillonage du capteur
    V = V*pow(10, -4); //Les valeurs étaient en %
    
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
}

