/**
* Implementation of KalmanFilter class.
*
* @author: Hayk Martirosyan
* @date: 2014.11.15
*/

#include <iostream>
#include <stdexcept>

#include "kalman.hpp"

KalmanFilter::KalmanFilter(
    double dt,
    const Eigen::MatrixXd& A,
    const Eigen::MatrixXd& C,
    const Eigen::MatrixXd& W,
    const Eigen::MatrixXd& V,
    const Eigen::MatrixXd& P)
  : A(A), C(C), W(W), V(V), P0(P),
    m(C.rows()), n(A.rows()), dt(dt), initialized(false),
    I(n, n), x_hat(n), x_hat_new(n)
{
  I.setIdentity();
}

KalmanFilter::KalmanFilter() {}

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

void KalmanFilter::update(const Eigen::VectorXd& y, const Eigen::VectorXd& Fobj) {

   Eigen::VectorXd  dy = Fobj -y;
  if(!initialized)
    throw std::runtime_error("Filter is not initialized!");

  x_hat_new = A * x_hat; //prédiction de l'état à t+1 x(k+1|k). u nul !
  P = A*P*A.transpose() + W; // 2.24 prédiction de l'erreur à t+1 P(k+1|k)
  K = P*C.transpose()*(C*P*C.transpose() + V*y).inverse(); // e W 2.27 donne K(t+1)
  x_hat_new += K * (y - C*x_hat_new); // x(k+1|k+1) état estimé à t+1 //idem u nul !
  P = (I - K*C)*P; // P(k+1|k+1) on calcule l'erreur d'estimation
  x_hat = x_hat_new;

  t += dt;
}

void KalmanFilter::update(const Eigen::VectorXd& y, const Eigen::VectorXd& Fobj, double dt, const Eigen::MatrixXd A) {

  this->A = A;
  this->dt = dt;
  update(y, Fobj);
}
