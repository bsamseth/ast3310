import matplotlib.pyplot as plt
# -------------------------------------------------------------------------------------------------------
# Assumptions:
# -------------------------------------------------------------------------------------------------------
# * R_values is an array of radii [unit: R_sun]
# * L_values is an array of luminosities (at each r) [unit: L_sun]
# * F_C_list is an array of convective flux ratios (at each r) [unit: relative value between 0 and 1]
# * n is the number of elements in both these arrays
# * R0 is the initial radius
# * show_every is a variable that tells you to show every ...th step (show_every = 50 worked well for me)
# * core_limit = 0.995 (when L drops below this value, we define that we are in the core)
# -------------------------------------------------------------------------------------------------------

# Cross-section of star
# (See https://stackoverflow.com/questions/9215658/plot-a-circle-with-pyplot and
# https://stackoverflow.com/questions/27629656/label-for-circles-in-matplotlib for details)


def cross_section_plot(R_values, L_values, F_C_list, n, R0,
                       show_every=50, core_limit=0.995, fill=True):
    plt.figure()
    ax = plt.gca()   # get current axis
    rmax = 1.2 * R0
    ax.set_xlim(-rmax, rmax)
    ax.set_ylim(-rmax, rmax)
    ax.set_aspect('equal')	 # make the plot circular
    first_convection, first_convection_radius = True, 0
    last_convection_radius = 0
    for k in range(0, n-1, show_every):
        if(L_values[k] > core_limit):  # outside core
            if(F_C_list[k] > 0.0):   # convection
                circR = plt.Circle((0, 0), R_values[k], color='red', fill=fill)
                ax.add_artist(circR)

                if first_convection:
                    first_convection_radius = R_values[k]
                    first_convection = False
                last_convection_radius = R_values[k]

            else:				# radiation
                circY = plt.Circle((0, 0), R_values[k], color='yellow', fill=fill)
                ax.add_artist(circY)

        else:				# inside core
            if(F_C_list[k] > 0.0):		# convection
                circB = plt.Circle((0, 0), R_values[k], color='blue', fill=fill)
                ax.add_artist(circB)
            else:				# radiation
                circC = plt.Circle((0, 0), R_values[k], color='cyan', fill=fill)
                ax.add_artist(circC)

    ax.add_artist(plt.Circle((0, 0), min(R_values), color='w', fill=True))

    circR = plt.Circle((2*rmax, 2*rmax), 0.1*rmax, color='red', fill=True)		# These are for the legend (drawn outside the main plot)
    circY = plt.Circle((2*rmax, 2*rmax), 0.1*rmax, color='yellow', fill=True)
    circC = plt.Circle((2*rmax, 2*rmax), 0.1*rmax, color='cyan', fill=True)
    circB = plt.Circle((2*rmax, 2*rmax), 0.1*rmax, color='blue', fill=True)
    # only add one (the last) circle of each colour to legend
    ax.legend([circR, circY, circC, circB],
              ['Convection outside core', 'Radiation outside core',
               'Radiation inside core', 'Convection inside core'])

    conv_frac = (first_convection_radius - last_convection_radius) / R0
    ax.set_xlabel(r'Outer convection layer: %.2f $R_0$' % conv_frac, size=20)
    ax.set_ylabel('')
    ax.tick_params(axis='both', which='major', labelsize=10)
    ax.set_title('Cross-section of star', size=18)

    return conv_frac
