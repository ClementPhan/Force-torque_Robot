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
                           double Fobj,
                           const Eigen::VectorXd& u,
                           const Eigen::MatrixXd& A,
                           const Eigen::MatrixXd& C,
                           const Eigen::MatrixXd& W,
                           const Eigen::MatrixXd& V,
                           const Eigen::MatrixXd& P)
: A(A), C(C), W(W), V(V), P0(P),
m(C.rows()), n(A.rows()), dt(dt), Fobj(Fobj), L(L),u(u), initialized(false),
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
    
    cout <<"init C" << C;
}

void KalmanFilter::init() {
    x_hat.setZero();
    P = P0;
    t0 = 0;
    t = t0;
    initialized = true;
}

void KalmanFilter::update(Eigen::VectorXd y) {
    c = 2; //why necessary ?
    double alpha;
    if(y(2) != 0){
        alpha = 0;
    }
    else{
        alpha = y(0)/y(2);
    }
    
    Eigen::VectorXd Fz(1);
    Fz << y(2);
    
    Eigen::MatrixXd B(n,n);
    B << sin(alpha), 0,
        0, 0;
    
    Eigen::MatrixXd D(m,c);
    D << 0, cos(alpha);
    
    /*Eigen::MatrixXd K(2,1);
    K << 0, 0;*/
    
    cout << "C" << C << endl;
    
    if(!initialized)
        throw std::runtime_error("Filter is not initialized!");
    
    x_hat_new = A * x_hat + B*u; //prédiction de l'état à t+1 x(k+1|k). u nul !
    P = A*P*A.transpose() + W; // 2.24 prédiction de l'erreur à t+1 P(k+1|k)
    K = P*C.transpose()*(C*P*C.transpose() + V).inverse(); // e W 2.27 donne K(t+1)
    x_hat_new += A*K*Fz - A*K*(C*x_hat + D*u); // x(k+1|k+1) état estimé à t+1 //idem u nul !
    P = (I - K*C)*P; // P(k+1|k+1) on calcule l'erreur d'estimation
    x_hat = x_hat_new;
    
    t += dt;

}


KalmanFilter KalmanFilter::setRobotKalman(double stepTime, double ForceObjective){
    
    n = 2; // Nombre d'états: 3 déplacements et 3 vitesses
    m = 1; // Nombre de mesures: les forces mesurées dans les trois directions par le capteur (repère de la surface)
    c = 2; // Nombre de commandes
    //outputs: (x, y, z, u, v, w) les déplacements sont relatifs à la trajectoire, les vitesses sont absolues
    
    
    Eigen::MatrixXd A(n,n);
    Eigen::MatrixXd C(m, n);
    Eigen::MatrixXd V(m,m);
    Eigen::MatrixXd W(n,n);
    Eigen::MatrixXd P(n,n);
    Eigen::VectorXd u(c);
    
    double k = 3.1*pow(10,-3); // Spring's stiffness (N/mm)
    
    double L = 0.035; // Tool's length (mm)
    
    double g = 9.81; //
    
    dt = stepTime; // Time step
    Fobj = ForceObjective;
    v_robot = 1;
    
    u << v_robot, Fobj;
    
    // Defining matrices
    
    
    
    A << 1, dt,
        0, 1;
    
    C << k, 0;
    
    double Fx = 2.;
    double Fz = 20.; // ordres de grandeurs des forces que l'on s'attend à rencontrer afin d'en déduire le bruit du capteur
    
    double dFx = 1*pow(10, -3);
    double dFz = 0.75*pow(10, -3);
    double dMy = 1.25*pow(10,-3);
    
    double zasp = 1.*pow(10,-3);
    double zrobot = 0.2*pow(10,-3);
    
    
    V << (Fz*dFz + zasp*zasp + zrobot*zrobot)/(1.96*1.96*dt);
    W << zrobot*zrobot/(1.96*1.96), 0,
    0, 0;
    
    
    // Calcul de P solution de l'équation de Ricatti discrète
    P <<  2.52438142*pow(10,-9) ,   9.03184257*pow(10,-25),
        9.03184257*pow(10,-25), 0;

    
    /*cout << "A: \n" << A << endl;
     cout << "B: \n" << C << endl;
     cout << " W: \n" <<  W << endl;
     cout << "R: \n" << V  << endl;
     cout << "P: \n" << P << endl;*/
    
    // Construct the filter
    KalmanFilter kf(dt, Fobj, L, u, A, C, W, V, P);
    
    
    // Best guess of initial states
    Eigen::VectorXd x0(n);
    x0 << 0, 0;
    //rajouter initialisation nulle
    kf.init(0, x0);
    
    std::cout << "hello" << endl;
    
    return kf;
}


