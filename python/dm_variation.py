import numpy as np
import os
import matplotlib.pyplot as plt

# make sure the executable is updated
os.system("cd ../build/ && make && cd -")

# the dm_scales that are going to be used
dm_scales = [0, 2, 10, 20, 30, 50, 100, 1000, 10000]
dm_scales = [0,50, 60, 75, 100, 200, 500]
dm_scales = [0, 50, 60, 75, 100, 200, 500, 1000]
dm_scales = [50, 60, 75, 100, 200, 500, 1000, 10000, 100000]
print dm_scales

# input scales to be used
R = 1
M = 1
rho = 0.04
T = 0.829


m_data = []
r_data = []

for dm_scale in dm_scales:
    filename = "output_dmscale_%.1E.dat" % dm_scale
    command = "cd ../build && ./main.x %g %g %g %g %g %s &> /dev/null" % (R,M,rho,T,dm_scale,filename)
    print "\nRunning with args: %g %g %g %g %g %s" % (R,M,rho,T,dm_scale,filename)
    os.system(command)
    outData = np.loadtxt("../build/" + filename)[:-1,0:2] # only fetch m and r data
    m_data.append(outData[:,0])
    r_data.append(outData[:,1])


plt.rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
plt.rc('text', usetex = True)
fig, ax = plt.subplots()
plt.hold('on')
for i, (m, r) in enumerate(zip(m_data, r_data)):
    m /= m[0]
    r /= r[0]

    ax.plot(m, r,
            label=(r'$M_0/dm = %s$' % ("%.f" % dm_scales[i] if (dm_scales[i] != 0) else "DSS")))

ax.set_title(r'$r(m)$ for various values of $dm$', size=24)
ax.set_ylabel(r'$R/R_0$', size=22)
ax.set_xlabel(r'$M/M_0$', size=22)
ax.legend(loc='best', prop={'size':20})
plt.show()
