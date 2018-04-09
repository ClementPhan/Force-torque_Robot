
/**
 * Kalman filter implementation using Eigen. Based on the following
 * introductory paper:
 *
 *     http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf
 *
 * @author: Hayk Martirosyan
 * @date: 2014.11.15
 */

#include <Eigen/Dense>
#include <mutex>

using namespace std;

#pragma once

class KalmanFilter {
    
public:
    
    /**
     * Create a Kalman filter with the specified matrices.
     *   A - System dynamics matrix
     *   C - Output matrix
     *   Q - Process noise covariance -> W
     *   R - Measurement noise covariance -> V (symétrique)
     *   P - Estimate error covariance
     */
    KalmanFilter(
                 double dt,
                 double L,
                 const Eigen::MatrixXd& A, // matrice de doubles de taille non définie
                 const Eigen::MatrixXd& C,
                 const Eigen::MatrixXd& Q,
                 const Eigen::MatrixXd& R,
                 const Eigen::MatrixXd& P
                 );
    
    // Create a blank estimator.
    KalmanFilter();
    
    // Create a Kalman filter adapted for the specific robot case
    KalmanFilter setRobotKalman(double stepTime);
    
    // Initialize the filter with initial states as zero.
    void init();

	
    
    // Initialize the filter with a guess for initial states.
    void init(double t0, const Eigen::VectorXd& x0);
    

    /* Update the estimated state based on measured values. The
        time step is assumed to remain constant.*/
    void update(Eigen::VectorXd & displacement, Eigen::VectorXd y, Eigen::VectorXd Fobj, Eigen::VectorXd rot, mutex & m);
    // Return the current state or time.
    Eigen::VectorXd getState() { return x_hat; };
    double getTime() { return t; };
    
    void random(mutex m);

private:
    
    // Matrices for computation
    Eigen::MatrixXd A, C, W, V, P, K, P0;
    
    // System dimensions
    int m, n;
    
    // Initial and current time
    double t0, t;
    
    // Discrete time step
    double dt;
    
    //Lenght of tool (specific to the robot)
    double L;
    
    // Is the filter initialized?
    bool initialized;
    
    // n-size identity
    Eigen::MatrixXd I;
    
    // Estimated states
    Eigen::VectorXd x_hat, x_hat_new;
};
