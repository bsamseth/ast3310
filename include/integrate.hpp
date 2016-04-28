#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <sstream>
#include <string>
#include <armadillo>

#include "massfractions.hpp"
#include "energy_production.hpp"
#include "constants.hpp"
#include "opacity.hpp"

/**
 * Namespace for methods related to integrating the governing equations of the star.
 *
 * The main method is `integrate`, and the others are convenience methods defining
 * the right hand sides (RHS) of the differential equations on the form du/dx = RHS(u,x).
 */
namespace Integrate {

  /**
   * Solve the 4 governing equations using the Forward Euler method.
   *
   * The method takes as input the initial (surface) condititons, and returns
   * a string containing the solution data, line by line in the following format:
   *
   *       m   r   P   L   T   rho   epsilon
   *
   * Note that if `dm` is given as zero, the method will use dynamic
   * step size (DSS) in the solution.
   *
   * @param L_0 Initial luminosity [J/s]
   * @param T_0 Initial temperature [K]
   * @param P_0 Initial pressure [N/m^2]
   * @param rho_0 Initial density [kg/m^3]
   * @param M_0 Total mass [kg]
   * @param R_0 Total radius [m]
   * @param MF The mass fractions for the star
   * @param dm The step size in mass to use. dm = 0 -> Use DSS
   * @return String with all data
   */
  std::string integrate(double L_0, double T_0, double P_0, double rho_0, double M_0, double R_0, MassFractions MF, double dm);

  std::string integrate_conv(double L_0, double T_0, double P_0, double rho_0, double M_0, double R_0, MassFractions MF, double dm);

  void calculate_convection(double T, double P, double r, double L,
                            double rho, double m, double mu_0,
                            double& nabla_radiative, double& nabla,
                            double& dTdm, double& F_C,
                            double& F_R, Opacity& kappa);

  inline double RHS_T(double T, double rho, double L, double r, Opacity& kappa) {
    return - 3 * kappa(T, rho) * L / (256 * Constants::pi*Constants::pi * Constants::sigma * r*r*r*r * T*T*T);
  }

  inline double RHS_P(double m, double r) {
    return - Constants::G * m / (4 * Constants::pi * r*r*r*r );
  }

  inline double RHS_r(double r, double rho) {
    return 1./(4 * Constants::pi * r*r * rho);
  }

  inline double nabla_ad() {
      return 0.4;
  }

  inline double nabla_rad(double T, double rho, double L, double P, double m, Opacity& kappa) {
      return (3. * kappa(T,rho) * L * P) /
             (64. * Constants::pi * Constants::sigma * Constants::G
                  * T*T*T*T * m);
  }
}

#endif
