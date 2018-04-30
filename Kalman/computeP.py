import numpy as np

import matplotlib.pyplot as plt
import scipy.linalg

k = 3.1*pow(10,3); 
    
L = 30.5*pow(10,-3); #rayon bille 6.5mm

m = 20*pow(10,-3);
    
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

zasp = pow(10,-3)
zrobot = 0.2*pow(10,-3)


def cov(x,y, Ex, Ey):
    return 


              
def var(Fx, PFx):
    return pow(Fx, 2)*PFx-pow(Fx*PFx,2);
              
              
### matrices modèles continu
A = np.array([0,1,
              0, 0], float).reshape(2,2);
C = np.array([k, 0],float).reshape(1,2);

V = np.array([var(Fz,PFz)+ var(zasp,k)-var(zrobot, k)], float).reshape(1,1)
             
W = np.array([0.0196]).reshape(1,1)
             
M = np.array([1,
             0], float).reshape(2,1)
            


### matrices modèle discret

Ad = np.exp(A*dt)

Cd = C

Vd = V/dt

Wd = dt*np.dot(M,np.dot(W, np.transpose(M)))

Md = np.identity(2)

### Résolution de l'équation de Riccati discrète 

P = scipy.linalg.solve_discrete_are(np.transpose(Ad), np.transpose(Cd), Wd, Vd);

print(P)

