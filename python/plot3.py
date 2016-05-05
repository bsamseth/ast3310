import numpy as np
import matplotlib.pyplot as plt
from cross_section_plot import cross_section_plot


data = np.loadtxt('../build/output.dat')

m = data[:, 0]
r = data[:, 1]
P = data[:, 2]
L = data[:, 3]
T = data[:, 4]
rho = data[:, 5]
eps = data[:, 6]
F_C = data[:, 7]
eps_PPI = data[:, 8]
eps_PPII = data[:, 9]
nabla = data[:, 10]
nabla_rad = data[:, 11]


R_sun = 6.96e8
L_sun = 3.846e26
M_sun = 1.989e30

m /= M_sun
r /= R_sun
L /= L_sun

plt.rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
plt.rc('text', usetex=True)

# flux plot
fig, ax = plt.subplots()
ax.set_ylim(-0.1, 1.1)
ax.plot(r, 1 - F_C, label=r'$F_R/F_{tot}$')
ax.plot(r, F_C, label=r'$F_C/F_{tot}$')
ax.legend(loc='best')
ax.set_xlabel(r'$R\ [R_\odot]$', size=22)

# energy production plot
fig, ax = plt.subplots()
ax.set_ylim(-0.1, 1.1)
ax.semilogx(T[1:], eps_PPI[1:] / (eps_PPI[1:] + eps_PPII[1:]), label=r'PPI')
ax.semilogx(T[1:], eps_PPII[1:] / (eps_PPI[1:] + eps_PPII[1:]), label=r'PPII')
ax.set_xlabel(r'$T$ [K]', size=22)
ax.legend(loc='best')

# cross section plot
n = len(r)
convection_fraction = cross_section_plot(r, L, F_C, n, r[0], fill=True)


fig, ax = plt.subplots()
ax.semilogy(r, [0.4]*n, label=r'$\nabla_{ad}$')
ax.semilogy(r, nabla, label=r'$\nabla$')
ax.semilogy(r, nabla_rad, label=r'$\nabla_{rad}$')
ax.legend(loc='best')
ax.set_xlabel(r'$R\ [R_\odot]$', size=22)


plt.show()
