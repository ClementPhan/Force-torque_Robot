#include <iostream>
#include <vector>
using namespace std;
#include <Eigen/Dense>

#include <time.h>
#include <chrono>
#include vector

#include "correcteur.hpp"

using namespace std::chrono;

int main(int argc, char* argv[]) {
    
    
    int n = 2;
    int m = 1;
    int c = 2;
    
    float dt = 0.001;
    double Fobj = 10;

    //initialize Filter
    KalmanFilter kf;
    kf = kf.setRobotKalman(dt, Fobj);
    
    // List of noisy position measurements (y)
    Eigen::MatrixXd measurements(3,3);
    measurements << 20*tan(3.14/3), 0, 20,
                    0, 0, 23,
                    0, 0, 20;
    
    measurements = measurements*pow(10,6);
    
    
    
    double  test[1000][2];
    for(int i = 0; i< 2; i++){
        test[0][i] = 0;
    }
    
    
    double copie[11][2];
    for(int i=1; i<12; i++){
        copie[i][0] = 6-i;
        copie[i][1] = 0.1*(i-1);
    }
    
    copie[0][0] = 11;
    

    
    // on calcule les moyennes
    double FzMoy = 0;
    double tMoy = 0;
    
    for(int j =1; j< copie[0][0]+1; j++){
        FzMoy += copie[j][0];
        tMoy += copie[j][1];
    }
    FzMoy /= copie[0][0];
    tMoy /= copie[0][0];
    
    
    double an = 0;
    double ad = 0;
    double a, b;
    //on effectue le calcul sur la copie
    for(int j =1; j< copie[0][0]+1; j++){
        an+= (copie[j][1]-tMoy)*(copie[j][0]-FzMoy);
        ad+= (copie[j][1]-tMoy)*(copie[j][1]-tMoy);
    }
    a = an/ad;
    b = FzMoy - a*tMoy;
    
    cout << " FzMoy "<< FzMoy << " tMoy "<< tMoy << " a " << a << " b " << b <<endl;
    
    
    return 0;
    
    
    /*// Feed measurements into filter, output estimated states
    float t = 0;
    for(int i = 0; i < measurements.rows(); i++) {
        t += dt;
        
        y = measurements.block<1,3>(i,0);
        cout << y << endl;
        kf.update(y);
        
        cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose() << endl 
        << ", x_hat[" << i << "] = " << kf.getState().transpose() << endl;
        cout <<""<<endl;
    }
    
    return 0;*/
}
