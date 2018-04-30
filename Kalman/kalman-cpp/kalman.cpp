/**
 * Implementation of KalmanFilter class.
 *
 * @author: Hayk Martirosyan
 * @date: 2014.11.15
 */

#include <iostream>
#include <stdexcept>
#include <time.h>

using namespace std;

#include "kalman.hpp"

KalmanFilter::KalmanFilter(){}

KalmanFilter::KalmanFilter(
                           double dt,
                           double L,
                           const Eigen::MatrixXd& A,
                           const Eigen::MatrixXd& C,
                           const Eigen::MatrixXd& W,
                           const Eigen::MatrixXd& V,
                           const Eigen::MatrixXd& P)
: A(A), C(C), W(W), V(V), P0(P),
m(C.rows()), n(A.rows()), dt(dt), L(L), initialized(false),
I(n, n), x_hat(n), x_hat_new(n)
{
    I.setIdentity();
}


void KalmanFilter::init(double t0, const Eigen::VectorXd& x0) {
    x_hat = x0;
    P = P0;
    this->t0 = t0;
    t = t0;
    initialized = true;
}

void KalmanFilter::init() {
    x_hat.setZero();
    P = P0;
    t0 = 0;
    t = t0;
    initialized = true;
}

void KalmanFilter::update(Eigen::VectorXd & displacement, Eigen::VectorXd y, Eigen::VectorXd Fobj, Eigen::VectorXd rot, mutex & m) {
    
    //double alpha;
    /*Eigen::VectorXd ySurf = y;
     ySurf(2) += y(4)*sin(alpha)*L;
     Eigen::VectorXd  dy = Fobj -ySurf;*/
    Eigen::VectorXd  dy = Fobj - y;
    
    if(!initialized)
        throw std::runtime_error("Filter is not initialized!");
    
    x_hat_new = A * x_hat; //prédiction de l'état à t+1 x(k+1|k). u nul !
    P = A*P*A.transpose() + W; // 2.24 prédiction de l'erreur à t+1 P(k+1|k)
    K = P*C.transpose()*(C*P*C.transpose() + V).inverse(); // e W 2.27 donne K(t+1)
    x_hat_new += K * (dy - C*x_hat_new); // x(k+1|k+1) état estimé à t+1 //idem u nul !
    P = (I - K*C)*P; // P(k+1|k+1) on calcule l'erreur d'estimation
    x_hat = x_hat_new;
    
    t += dt;
    
    std::lock_guard<std::mutex> guard(m);
    displacement = x_hat;
}


KalmanFilter KalmanFilter::setRobotKalman(double stepTime){
    
    
    
    cout << "Hello" << endl;
    
    n = 6; // Nombre d'états: 3 déplacements et 3 vitesses
    m = 6; // Nombre de mesures: les forces mesurées dans les trois directions par le capteur (repère de la surface)
    //outputs: (x, y, z, u, v, w) les déplacements sont relatifs à la trajectoire, les vitesses sont absolues
    
    
    Eigen::MatrixXd A(n,n);
    Eigen::MatrixXd C(m, n);
    Eigen::MatrixXd V(m,m);
    Eigen::MatrixXd W(n,n);
    Eigen::MatrixXd P(n,n);
    
    int k = 2; // Spring's stiffness (N/mm)
    
    int L = 100; // Tool's length (mm)
    
    double g = 9.81*pow(10,-3); //
    
    dt = stepTime; // Time step
    
    // Defining matrices
    
    /*A << 1, 0, 0, dt, 0, 0,
     0, 1, 0, 0, dt, 0,
     0, 0, 1, 0, 0, dt,
     0, 0, 0, 1, 0, 0,
     0, 0, 0, 0, 1, 0,
     0, 0, 1/dt, 0, 0, 0;*/
    
    
    
    A << 1, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0,
    0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0;
    
    C << 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    0, 0, k*dt, 0, 0, 0;  // DeltaF = k*Deltax = k*v*dt
    
    Eigen::MatrixXd ligne(1,6);
    ligne << pow(10,-4), pow(10,-4), pow(10,-4), pow(10,-4), pow(10,-4), pow(10,-4); // précision du déplacement du robot
    
    W << ligne, ligne, ligne, ligne, ligne, ligne;
    
    double Fx = 1.*1.;
    double Fy = 1.*1.25;
    double Fz = 10.*0.75; // ordres de grandeurs des forces que l'on s'attend à rencontrer afin d'en déduire le bruit du capteur
    double Mx = 1.*1.;
    double My = 1.*1.25;
    double Mz = (g*L/2.)*1.5;
    
    V << Fx*Fx, Fx*Fy, Fx*Fz, Fx*Mx, Fx*My, Fx*Mz,
    Fx*Fz, Fy*Fy, Fy*Fz, Fy*Mx, Fy*My, Fy*Mz,
    Fx*Fz, Fy*Fz, Fz*Fz, Fz*Mx, Fz*My, Fz*Mz,
    Fx*Mx, Fy*Mx, Fz*Mx, Mx*Mx, Mx*My, Mx*Mz,
    Fx*My, Fy*My, Fz*My, Mx*My, My*My, My*Mz,
    Fx*Mz, Fy*Mz, Fz*Mz, Mx*Mz, My*Mz, Mz*Mz; //Les valeurs sont les valeurs de précision de la mesure indiquées sur le certificat d'échantillonage du capteur
    V = V*pow(10, -4); //Les valeurs étaient en %
    
    // Calcul de P: AP + PAt -Pctv-1Cp +MWMt = 0
    P = W;
    
    /*cout << "A: \n" << A << endl;
     cout << "B: \n" << C << endl;
     cout << " W: \n" <<  W << endl;
     cout << "R: \n" << V  << endl;
     cout << "P: \n" << P << endl;*/
    
    // Construct the filter
    KalmanFilter kf(dt, L, A, C, W, V, P);
    
    // Best guess of initial states
    Eigen::VectorXd x0(n);
    //rajouter initialisation nulle
    kf.init(0, x0);
    
    return kf;
}


