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
nabla = data[:, 9]
nabla_rad = data[:, 10]


R_sun = 6.96e8
L_sun = 3.846e26
M_sun = 1.989e30

m /= M_sun
r /= R_sun
L /= L_sun

plt.rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
plt.rc('text', usetex=True)

# energy production plot
fig, ax = plt.subplots()

max_eps = max(eps)
# ax.semilogy(reps, eps_skip, label=r'$\epsilon/\epsilon_{max}$')
ax.semilogy(r, eps_PPI, label=r'PPI')
ax.semilogy(r, (eps - eps_PPI), label=r'PPII')
ax.legend()

# cross section plot
n = len(r)
cross_section_plot(r, L, F_C, n, r[0], show_every=25, fill=True)

# temperture gardients plot TODO: Fix temperture gradient plots
fig, ax = plt.subplots()
ax.semilogy(r, [0.4]*n, label=r'$\nabla_{ad}$')
ax.semilogy(r, nabla, label=r'$\nabla$')
ax.semilogy(r, nabla_rad, label=r'$\nabla_{rad}$')
ax.legend()

plt.show()
