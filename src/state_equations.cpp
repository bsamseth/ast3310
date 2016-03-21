#include "particles.h"
#include "constants.h"
#include "massfractions.h"
#include "state_equations.h"

using namespace Particles;


//namespace SateEquations {
  /**
   * mu_0 = 1 / sum [ number of elements provided per nucleus X mass fraction / number of elements in core ]
   */
double StateEquations::mu_0(MassFractions MF) {
  double sum = 0;
  for (int particle = _p; particle < N_PARTICLES; particle++) 
    sum += (available_ionized_electrons[particle] + 1) * MF[particle] / core_elements[particle];
  sum += MF.Z / 2.0;
  return 1./sum;
}

double StateEquations::rho(double T, double P, double mu_0) {
  return (P - Constants::a/3 * T*T*T*T) * mu_0 * Constants::m_u / (Constants::k_b * T);
}

double StateEquations::P(double T, double rho, double mu_0) {
  return rho / (mu_0*Constants::m_u) * Constants::k_b * T + Constants::a/3 * T*T*T*T;
}
//}
