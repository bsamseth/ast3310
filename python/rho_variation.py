import numpy as np
import os
import matplotlib.pyplot as plt

# make sure the executable is updated
os.system("cd ../build/ && make && cd -")

# the rho that are going to be used
rho_scales = [0.05, 0.1, 0.25, 0.5, 0.75, 1]

# input scales to be used
R = 1
M = 1
T = 0.829
dm = 0 # use dss


allData = []

for rho_scale in rho_scales:
    filename = "output_rhoscale_%.1E.dat" % rho_scale
    command = "cd ../build && ./main.x %g %g %g %g %g %s &> /dev/null" % (R,M,rho_scale,T,dm,filename)
    print "\nRunning with args: %g %g %g %g %g %s" % (R,M,rho_scale,T,dm,filename)
    os.system(command)
    outData = np.loadtxt("../build/" + filename)[:-1,:]
    allData.append(outData)


plt.rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
plt.rc('text', usetex = True)
mfig = plt.figure().gca()
Pfig = plt.figure().gca()
Lfig = plt.figure().gca()
Tfig = plt.figure().gca()
rhofig = plt.figure().gca()
plt.hold('on')
for i, data in enumerate(allData):
    m = data[:,0] / data[0,0]
    r = data[:,1] / data[0,1]
    P = data[:,2] / data[0,2]
    L = data[:,3] / data[0,3]
    T = data[:,4] / data[0,4]
    rho = data[:,5] / data[0,5]

    mfig.plot(r, m,
            label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))
    Pfig.semilogy(r, P,
            label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))
    Lfig.plot(r, L,
              label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))
    Tfig.plot(r, T,
              label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))
    rhofig.semilogy(r, rho,
                label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))

mfig.set_title(r'$m(r)$ for various initial temperatures')
mfig.set_xlabel(r'$r/R_0$')
mfig.set_ylabel(r'$m/M_0$')

Pfig.set_title(r'$P(r)$ for various initial temperatures')
Pfig.set_xlabel(r'$r/R_0$')
Pfig.set_ylabel(r'$P/P_0$')

Lfig.set_title(r'$L(r)$ for various initial temperatures')
Lfig.set_xlabel(r'$r/R_0$')
Lfig.set_ylabel(r'$L/L_0$')

Tfig.set_title(r'$T(r)$ for various initial temperatures')
Tfig.set_xlabel(r'$r/R_0$')
Tfig.set_ylabel(r'$T/T_0$')

rhofig.set_title(r'$\rho(r)$ for various initial temperatures')
rhofig.set_xlabel(r'$r/R_0$')
rhofig.set_ylabel(r'$\rho/\rho_0$')

for cax in [mfig,Pfig,Lfig,Tfig,rhofig]:
    box = cax.get_position()
    cax.set_position([box.x0, box.y0, box.width * 0.85, box.height])
    cax.legend(loc='center left', bbox_to_anchor=(1, 0.5))


plt.figure()
#################

import matplotlib.gridspec as gridspec
gs = gridspec.GridSpec(4, 4)
gs.update( wspace=0.75)
ax1 = plt.subplot(gs[0, 0:2])
ax2 = plt.subplot(gs[0,2:])
ax3 = plt.subplot(gs[1,0:2])
ax4 = plt.subplot(gs[1,2:])
ax5 = plt.subplot(gs[2,0:2])
fig = plt.gcf()
#gs.tight_layout(fig)
ax = [ax1,ax2,ax3,ax4,ax5]


for i, data in enumerate(allData):
    m = data[:,0] / data[0,0]
    r = data[:,1] / data[0,1]
    P = data[:,2] / data[0,2]
    L = data[:,3] / data[0,3]
    T = data[:,4] / data[0,4]
    rho = data[:,5] / data[0,5]

    ax[0].plot(r, m,
            label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))
    ax[1].semilogy(r, P,
            label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))
    ax[2].plot(r, L,
              label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))
    ax[3].plot(r, T,
              label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))
    ax[4].semilogy(r, rho,
                label=(r'$\rho_0/\rho_{0,i}=%s$' % rho_scales[i]))

#ax[0].set_title(r'$m(r)$ for various radii')
#ax[0].set_xlabel(r'$r/R_0$',size=20)
ax[0].set_ylabel(r'$m/M_0$',size=20)

#ax[1].set_title(r'$P(r)$ for various radii')
#ax[1].set_xlabel(r'$r/R_0$',size=20)
ax[1].set_ylabel(r'$P/P_0$',size=20)

#ax[2].set_title(r'$L(r)$ for various radii')
#ax[2].set_xlabel(r'$r/R_0$',size=20)
ax[2].set_ylabel(r'$L/L_0$',size=20)

#ax[3].set_title(r'$T(r)$ for various radii')
ax[3].set_xlabel(r'$r/R_0$',size=20)
ax[3].set_ylabel(r'$T/T_0$',size=20)

#ax[4].set_title(r'$\rho(r)$ for various radii')
ax[4].set_xlabel(r'$r/R_0$',size=20)
ax[4].set_ylabel(r'$\rho/\rho_0$',size=20)

cax = ax[-1]
box = cax.get_position()
#cax.set_position([box.x0, box.y0, box.width * 0.85, box.height])
cax.legend(loc='center left', bbox_to_anchor=(1.4, 0.25))



    
    
# ax[0,0].set_title(r'Solutions for different starting radii, $R_0$', size=18)
# ax[0,0].set_ylabel(r'$M/M_0$', size=16)
# ax[0,0].set_xlabel(r'$R/R_0$' + '\nRun: ./main.x %g %g %g %g' % (1,1,0.04,0.829), size=16)
#ax[0,0].legend(loc='best', prop={'size':16})
plt.show()
