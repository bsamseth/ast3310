#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <sstream>
#include <string>
#include <armadillo>

#include "massfractions.h"
#include "energy_production.h"
#include "constants.h"
#include "opacity.h"

namespace Integrate {
  
  std::string integrate(double L_0, double T_0, double P_0, double rho_0, double M_0, double R_0, MassFractions MF, double dm);

  inline double RHS_T(double T, double rho, double L, double r) {
    return - 3 * opacity(T, rho) * L / (256 * Constants::pi*Constants::pi * Constants::sigma * r*r*r*r * T*T*T);
  }

  inline double RHS_L(double T, double rho, MassFractions MF, arma::mat& terms) {
    return EnergyProduction::energy(T, rho, MF, terms);
  }

  inline double RHS_P(double m, double r) {
    return - Constants::G * m / (4 * Constants::pi * r*r*r*r );
  }

  inline double RHS_r(double r, double rho) {
    return 1./(4 * Constants::pi * r*r * rho);
  }
}

#endif
