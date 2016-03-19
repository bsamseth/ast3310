import numpy as np
import os
import subprocess as sp


def fetch_cond_from_file(R,M,rho,T):
    data = np.loadtxt("cond_tester_data.dat")

    #print "data = ", data

    try:
        i_R_all = np.where(abs(data[:,0]-R)<1e-4)[0]
        i_M = np.where(abs(data[:,1]-M)<1e-4)[0]
        i_rho = np.where(abs(data[:,2]-rho)<1e-4)[0]
        i_T = np.where(abs(data[:,3]-T)<1e-4)[0]

        #print i_R_all, i_M, i_rho, i_T
    except (Exception):
        #   print "exception"
        return None

    for i_R in i_R_all:
        if i_R in i_M and i_R in i_rho  and i_R in i_T:
            return data[i_R,-1]

    return None
    
        
def write_cond_to_file(R,M,rho,T,zero):
    with open("cond_tester_data.dat",'a') as f:
        print >>f, "%g %g %g %g %g" % (R,M,rho,T,zero)



L_0   = 1  * 3.846e26
R_0   = 0.72 * 6.96e8
M_0   = 1 * 1.989e30
rho_0 = 5.1  * 1.408e3
T_0   = 5.7e6
P_0 = 5.5e14


# m 	 r 	 P 	 L 	 T 	 rho


# running first with default param to have a baseline
command = "cd ../build && ./main.x %g %g %g %g" % (1,1,1,1)
print "\nRunning with args: %g %g %g %g" % (1,1,1,1)
output = sp.check_output(command, shell=True)
print output.split('\n')[:-1]
numbers = [float(i) for i in output.split()]
m_new, r_new, P_new, L_new, T_new, rho_new, dm_new = numbers

best_zerosness = m_new/M_0 + r_new / R_0 + L_new / L_0

write_cond_to_file(1,1,1,1,0.2685)

best_zero = [1,1,1,1]
print "Best param: ", best_zero, "with zerosness = ", best_zerosness



R_scale = [1]#np.linspace(0.5,5,10)
M_scale = [1]#np.linspace(0.5,2,10)
rho_scale = [0.04]#np.logspace(-2,1,6)
T_scale = np.linspace(0.5,5,15)



for R in R_scale:
    for M in M_scale:
        for rho in rho_scale:
            for T in T_scale:
                fetched = fetch_cond_from_file(R,M,rho,T)
                if fetched == None:
                    command = "cd ../build && ./main.x %g %g %g %g" % (R,M,rho,T)
                    print "\nRunning with args: %g %g %g %g" % (R,M,rho,T)
                    output = sp.check_output(command, shell=True)
                    numbers = [float(i) for i in output.strip().split()]
                    m_new, r_new, P_new, L_new, T_new, rho_new, dm_new = numbers

                    zerosness = m_new/M_0 + r_new / R_0 + L_new / L_0

                    write_cond_to_file(R,M,rho,T,zerosness)
                else:
                    print "\nRunning with args: %g %g %g %g (fetched from file)" % (R,M,rho,T)
                    zerosness = fetched
                
                if zerosness < best_zerosness:
                    best_zero = [R,M,rho,T]
                    best_zerosness = zerosness
                    
                print output.split('\n')[:-1]
                print "Best param: ", best_zero, "with zerosness = ", best_zerosness



