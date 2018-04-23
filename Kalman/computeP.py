import numpy as np

import matplotlib.pyplot as plt
import scipy.linalg

k = 2; 
    
L = 100;

m = 1;
    
g = 9.81*pow(10,-3); 

dt = 0.01;


Fx = 1.
PFx = 0.01

Fy = 1.
PFy = 0.0125

Fz = 20.
PFz = 0.0075

Mx = 1.
PMx = 0.01

My = 1.
PMy = 0.0125

Mz = g*L/2.
PMz = 0.015


def cov(x,y, Ex, Ey):
    return 


"""A = np.array([0,0,0,1,0,0,
              0,0,0,0,1,0,
              0,0,0,0,0,1,
              0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,k/m,0,0,0], float).reshape(6,6);

C = np.array([0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,k,0,0,0,
              0,0,0,0,0,0,
              0,0,0,0,0,0,
              0,0,0,0,0,0], float).reshape(6,6);

W = np.array([0.0196,0,0,0,0,0,0,
             0,0.0196,0,0,0,0,0,
             0,0,0.0196,0,0,0,0,
             0,0,0,0.0196,0,0,0,
             0,0,0,0,0.0196,0,0,
             0,0,0,0,0,0.0196,0,
             0,0,0,0,0,0,0.09], float).reshape(7,7);

M = np.array([0,0,0,1,0,0,0,
             0,0,0,0,1,0,0,
             0,0,0,0,0,1,0,
             0,0,0,0,0,0,1,
             0,0,0,0,0,0,0,
             0,0,k/m,0,0,0,k/m], float).reshape(6,7);

Q = np.dot(M,np.dot(W, np.transpose(M)))



V = np.array([var(Fx,PFx), 0, 0, 0, 0, 0,
              0, var(Fy,PFy), 0, 0, 0, 0,
              0, 0, var(Fz,PFz), 0, 0, 0,
              0, 0, 0, var(Mx,PMx), 0, 0,
              0, 0, 0, 0, var(My,PMy), 0,
              0, 0, 0, 0, 0, var(Mz,PMz)], float).reshape(6,6);"""
              
def var(Fx, PFx):
    return pow(Fx, 2)*PFx-pow(Fx*PFx,2);
              
A = np.array([0,1,
              0, 0], float).reshape(2,2);
C = np.array([k, 0],float).reshape(1,2);

V = np.array([var(Fz,PFz)], float).reshape(1,1)
             
W = np.array([0.0196, 0, 
             0, 0.09]).reshape(2,2)
             
M = np.array([1, 0, 
            0, k/m], float).reshape(2,2)
            
Q = np.dot(M,np.dot(W, np.transpose(M))) 


P = scipy.linalg.solve_continuous_are(np.transpose(A), np.transpose(C), Q, V);

print(P)

