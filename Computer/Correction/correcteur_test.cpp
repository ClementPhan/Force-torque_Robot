#include <iostream>
#include <vector>
using namespace std;
#include <Eigen/Dense>

#include <time.h>
#include <chrono>
<<<<<<< HEAD
#include vector
=======
#include <stdio.h>
>>>>>>> correction_alternative

#include "correcteur.hpp"

using namespace std::chrono;


double winsorize(double* data){
    /*double max = data[1];
    double min = max;*/
    double V = 0;
    double mean = 0;
    double N = data[0];
    for(int i=1; i< N+1; i++){
        /*if(data[i] > max){
            max = data[i];
        }
        if(data[i] < min){
            min = data[i];
        }*/
        mean += data[i];
        V += data[i]*data[i];
    }
    mean /= N;
    V = V/N-mean*mean;
    double Ec = sqrt(V);
    
    for(int i=1; i < N+1; i++){
        if(data[i] > mean + Ec/sqrt(N)){
            data[i] = mean;
        }
        if(data[i] < mean - Ec/sqrt(N)){
            data[i] = mean;
        }
    }
    mean = 0;
    for(int i=1; i < N+1; i++){
        mean += data[i];
    }
    mean /= N;
    
    for(int i= 1; i < N+1; i++){
        cout << data[i] << " " << flush;
    }
    cout << endl;
    
    return mean;
};

int main(int argc, char* argv[]) {
    
    
    double data[11] = {10, 0, 0.7, 0, 1.3, 0, 0, 0, 0, 0, 0};
    double mean = 0;
    for(int i=1; i< data[0]+1; i++){
        mean += data[i];
    }
    mean /= data[0];
    cout << mean << endl;

    cout << winsorize(data) <<endl;
    

    
    
    
    
    
    
    /*int n = 2;
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
    
    cout << " FzMoy "<< FzMoy << " tMoy "<< tMoy << " a " << a << " b " << b <<endl;*/
    
    
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
