#include <gtest/gtest.h>
#include <iostream>

#include "particles.h"
#include "constants.h"
#include "state_equations.h"
#include "massfractions.h"
#include "energy_production.h"

using std::cout;
using std::endl;
using namespace Particles;
//using namespace StateEquations;

const double eps = 1e-13;

TEST (Mean_Molecular_Weight, only_hydrogen) {
  MassFractions MF;
  MF.X = 1;
  MF.setFractions();
  EXPECT_NEAR(0.5, StateEquations::mu_0(MF), 0.5*eps);
}

TEST (Mean_Molecular_Weight, hydrogen_and_helium) {
  MassFractions MF;
  MF.X = 0.5;
  MF.Y4 = 0.5;
  MF.setFractions();
  EXPECT_NEAR(8./11, StateEquations::mu_0(MF), 8./11 * eps );
}

TEST (Mean_Molecular_Weight, comp_with_alternate_calculation) {
  MassFractions MF;
  MF.X = 0.5;
  MF.Y4 = 0.5;
  MF.setFractions();
  double n_tot = 0;
  double rho_input = Constants::Sun::Core::rho*0.123; // value should not matter
  for (int p = _e; p < N_PARTICLES; p++) {
    n_tot += EnergyProduction::n_density(Particle(p), MF, rho_input);
  }
  double mu_0_alternate = (rho_input/n_tot) / Constants::m_u;
  EXPECT_NEAR(StateEquations::mu_0(MF), mu_0_alternate, eps);
}

TEST (Rho_P_sanity, rho_of_P_of_rho_is_rho) {
  MassFractions MF;
  MF.X = 1;
  MF.setFractions();
  double mu_0 = StateEquations::mu_0(MF);
  
  double T = Constants::Sun::Core::T;
  double rho_input = Constants::Sun::Core::rho;
  double rho_output = StateEquations::rho(T, StateEquations::P(T,rho_input,mu_0),mu_0);

  EXPECT_NEAR(rho_input, rho_output, eps*rho_input);
}

TEST (Rho_P_sanity, P_of_rho_of_P_is_P) {
  MassFractions MF;
  MF.X = 1;
  MF.setFractions();
  double mu_0 = StateEquations::mu_0(MF);
  
  double T = Constants::Sun::Core::T;
  double P_input = Constants::Sun::Core::P;
  double P_output = StateEquations::P(T, StateEquations::rho(T,P_input,mu_0),mu_0);

  EXPECT_NEAR(P_input, P_output, eps*P_input);
}


