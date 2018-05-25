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

#include "correcteur.hpp"

KalmanFilter::KalmanFilter(){}

KalmanFilter::KalmanFilter(
                           double dt,
                           double L,
                           double Fobj,
                           double k,
                           double v_robot,
                           const Eigen::VectorXd& u,
                           const Eigen::MatrixXd& A,
                           const Eigen::MatrixXd& C,
                           const Eigen::MatrixXd& W,
                           const Eigen::MatrixXd& V,
                           const Eigen::MatrixXd& P)
: A(A), C(C), W(W), V(V), P0(P),
m(C.rows()), n(A.rows()), dt(dt), Fobj(Fobj), L(L), k(k), v_robot(v_robot), u(u), initialized(false),
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

double KalmanFilter::update(Eigen::VectorXd y) {
    y = y*pow(10,-6); // on enlève le gain d'un million
    
    c = 2; //why necessary ?
    /*double alpha;
    if(y(2) == 0){
        alpha = 0;
    }
    else{
        alpha = atan(y(0)/y(2));
    }
    
    int Fz = y(2);
    
    double x = (1/k)*(Fz-Fobj*cos(alpha)) + sin(alpha)*v_robot;*/
    
    double Fn = pow(y(0)*y(0) + y(1)*y(1) + y(2)*y(2), 1/2);

    double x = (1/k)*(Fn-Fobj); // la correction de pente sera ajoutée par le PID


    return x;

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
    
    k = 3.1*pow(10,3); // Spring's stiffness (N/m)
    
    L = 0.035; // Tool's length (mm)
    
    double g = 9.81; //
    
    dt = stepTime; // Time step
    Fobj = ForceObjective;
    v_robot = 1;
    
    u << v_robot, Fobj;
    
    // Defining matrices
    
    
    
    A << 0, 1,
        0, 0;
    
    C << k, 0;
    
    double Fx = 2.;
    double Fz = 20.; // ordres de grandeurs des forces que l'on s'attend à rencontrer afin d'en déduire le bruit du capteur
    
    double dFx = 1*pow(10, -3);
    double dFz = 0.75*pow(10, -3);
    double dMy = 1.25*pow(10,-3);
    
    double zasp = 1.*pow(10,-3);
    double zrobot = 0.2*pow(10,-3);
    
    
    V << (Fz*dFz)/(1.96*1.96*dt);
    W << (2*pow(zrobot*k, 2) + pow(zasp*k, 2))/(1.96*1.96), 0,
    0, 0;
    
    
    // Calcul de P solution de l'équation de Ricatti discrète
    P <<  2.70229612*pow(10,-0) ,   3.40417948*pow(10,-22),
        3.40417948*pow(10,-22), 0;

    
    /*cout << "A: \n" << A << endl;
     cout << "B: \n" << C << endl;
     cout << " W: \n" <<  W << endl;
     cout << "R: \n" << V  << endl;
     cout << "P: \n" << P << endl;*/
    
    // Construct the filter
    KalmanFilter kf(dt, L, Fobj, k, v_robot, u, A, C, W, V, P);
    
    
    // Best guess of initial states
    Eigen::VectorXd x0(n);
    x0 << 0, 0;
    //rajouter initialisation nulle
    kf.init(0, x0);
    
    
    return kf; 

}


