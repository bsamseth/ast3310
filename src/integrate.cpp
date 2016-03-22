#include <sstream>
#include <iostream>
#include <armadillo>
#include <cmath>
#include <algorithm>
#include <string>

#include "particles.h"
#include "constants.h"
#include "energy_production.h"
#include "massfractions.h"
#include "state_equations.h"
#include "integrate.h"
#include "opacity.h"


using namespace Constants;
using namespace Particles;
using namespace Integrate;
using EnergyProduction::energy;
using std::abs;
using std::min;
using std::min_element;


std::string Integrate::integrate(double L_0, double T_0, double P_0, double rho_0, double M_0, double R_0, MassFractions MF, double dm) {
  std::stringstream ss;
  ss << "# m \t r \t P \t L \t T \t rho \n";
  
  arma::mat energy_terms (N_PARTICLES, N_PARTICLES);
  
  double r = R_0, T = T_0, L = L_0, P = P_0, rho = rho_0, m = M_0;
  double drdm, dPdm, dLdm, dTdm;
  double mu_0 = StateEquations::mu_0(MF);

  Opacity kappa;

  double p_max = 0.005; // max fractional change in any variable
  double dms [5];
  
  int count = 0;

  bool dss = false;
  if (dm == 0) {
    dss = true;
    dm = -1e10;
  }

  std::cout << "Using dynamic step = " << (dss==true ? "true" : "false") << " M_0 = " << m << std::endl;
  while (m > 0 and r > 0 and L > 0 and T > 0 and rho > 0) {
    if (count++ % 10 == 0) {
      ss << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << '\n';
    }
    if (count % 100 == 0) {
      //double percent = 100 - (m / M_0) * 100;
      //std::cout << "\rProgress: " << percent << "%  ";
      std::cout << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << ' ' << dm << '\n';
    }
    
    
    drdm = RHS_r(r, rho);
    dPdm = RHS_P(m, r);
    dLdm = RHS_L(T, rho, MF, energy_terms);
    dTdm = RHS_T(T, rho, L, r, kappa);

    if (dss) {
      dms[0] = abs(p_max*r / drdm);
      dms[1] = abs(p_max*P / dPdm);
      dms[2] = abs(p_max*L / dLdm);
      dms[3] = abs(p_max*T / dTdm);
      dms[4] = abs(p_max*m);
      dm = - (*min_element(dms, dms+5));
      
      
      // while (abs(dm) > abs(dm_max) or abs(dm) < abs(dm_min) ){
      // 	if (abs(dm) > abs(dm_max))
      // 	  dm *= 0.99;
      // 	if (abs(dm) < abs(dm_min)) 
      // 	  dm *= 1.01;
      // }
    }
    
    r += drdm * dm;
    P += dPdm * dm;
    L += dLdm * dm;
    T += dTdm * dm;
    rho = StateEquations::rho(T, P, mu_0);
    m += dm;

    if (m < 0 or r < 0 or L < 0 or T < 0 or rho < 0 or dm > -1) {
      std::cout << "Unphysical at count = " << count << '\n'
		<< "dm = " << dm << '\n'
		<< "m/M_0 = " << m/M_0 << '\n'
		<< "r/R_0 = " << r/R_0 << '\n'
		<< "L/L_0 = " << L/L_0 << '\n'
      		<< "T = " << T << '\n'
		<< "rho = " << rho << '\n';
      break;
    }
  }

  std::cout << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << ' ' << dm << '\n';
  ss << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho;
  return ss.str();
}
