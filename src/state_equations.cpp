#include "particles.hpp"
#include "constants.hpp"
#include "massfractions.hpp"
#include "state_equations.hpp"

using namespace Particles;


double StateEquations::mu_0(MassFractions MF) {
  double sum = 0;
  for (int particle = _p; particle < N_PARTICLES; particle++)
    sum += (available_ionized_electrons[particle] + 1) * MF[particle] / core_elements[particle];
  return 1./sum;
}

double StateEquations::rho(double T, double P, double mu_0) {
  return (P - Constants::a/3 * T*T*T*T) * mu_0 * Constants::m_u / (Constants::k_b * T);
}

double StateEquations::P(double T, double rho, double mu_0) {
  return rho / (mu_0*Constants::m_u) * Constants::k_b * T + Constants::a/3 * T*T*T*T;
}
