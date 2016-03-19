import numpy as np

data = np.loadtxt("cond_tester_data.dat")
minimum = np.min(data[:,-1])
index = np.where(data[:,-1] == np.min(data[:,-1]))[0][0]
print "M, R, rho, T, zeros = ",
print data[index,:]
