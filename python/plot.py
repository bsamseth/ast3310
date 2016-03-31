import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('../build/output.dat')

m = data[:,0]
r = data[:,1]
P = data[:,2]
L = data[:,3]
T = data[:,4]
rho = data[:,5]
eps = data[:,6]

m /= m[0]
r /= r[0]
L /= L[0]
rho /= rho[0]
P /= P[0]

fig, ax = plt.subplots(3,2)

ax[0,0].plot(r, m)
ax[0,0].set_ylabel(r'$M/M_0$')
ax[0,0].set_xlabel(r'$R/R_0$')

ax[0,1].plot(r, T)
ax[0,1].set_xlabel(r'$R/R_0$')
ax[0,1].set_ylabel(r'$T/T_0$')

ax[1,0].plot(r, L)
ax[1,0].set_xlabel(r'$R/R_0$')
ax[1,0].set_ylabel(r'$L/L_0$')

ax[1,1].semilogy(r, eps)
ax[1,1].set_xlabel(r'$R/R_0$')
ax[1,1].set_ylabel(r'$\epsilon$')

ax[2,0].semilogy(r, P)
ax[2,0].set_xlabel(r'$R/R_0$')
ax[2,0].set_ylabel(r'$P/P_0$')

ax[2,1].semilogy(r, rho)
ax[2,1].set_xlabel(r'$R/R_0$')
ax[2,1].set_ylabel(r'$\rho/\rho_0$')


# fig, ax = plt.subplots(2,2)

# ax[0,0].plot(m, r)
# ax[0,0].set_ylabel('R/R_0')
# ax[0,0].set_xlabel('M/M_0')

# ax[0,1].plot(m, L)
# ax[0,1].set_xlabel('M/M_0')
# ax[0,1].set_ylabel('L/L_0')

# ax[1,0].plot(m, T)
# ax[1,0].set_xlabel('M/M_0')
# ax[1,0].set_ylabel('T/T_0')

# ax[1,1].semilogy(m, rho)
# ax[1,1].set_xlabel('M/M_0')
# ax[1,1].set_ylabel('rho/rho_0*5.1')


plt.show()
