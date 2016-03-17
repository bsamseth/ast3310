#include <sstream>
#include <iostream>
#include <armadillo>

#include "particles.h"
#include "constants.h"
#include "energy_production.h"
#include "massfractions.h"
#include "state_equations.h"
#include "integrate.h"
#include "opacity.h"


using namespace Constants;
using namespace Particles;
using EnergyProduction::energy;


std::stringstream Integrate::integrate(double L_0, double T_0, double P_0, double rho_0, double M_0, double R_0, MassFractions MF, double dm) {
  std::stringstream ss;
  ss << "# m \t r \t P \t L \t T \t rho \n";
  
  arma::mat energy_terms (N_PARTICLES, N_PARTICLES);
  
  double r = R_0, T = T_0, L = L_0, P = P_0, rho = rho_0, m = M_0;
  double dr, dP, dL, dT;
  double mu_0 = StateEquations::mu_0(MF);

  int count = 0;
  
  while (m > M_0*0.05) {
    if (count % 50 == 0)
      ss << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << '\n';
    
    dr = 1./(4 * pi * r*r * rho) * dm;
    dP = - G*m / (4 * pi * r*r*r*r ) * dm;
    dL = energy(T, rho, MF, energy_terms) * dm;
    dT = - 3 * opacity(T, rho) * L / (256 * pi*pi * sigma * r*r*r*r * T*T*T) * dm;

    r += dr;
    P += dP;
    L += dL;
    T += dT;
    rho = StateEquations::rho(T, P, mu_0);
    m += dm;
  }

  ss << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho;
  return ss;
}
