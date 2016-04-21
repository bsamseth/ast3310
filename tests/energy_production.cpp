#include <gtest/gtest.h>
#include <armadillo>
#include <cmath>

#include "energy_production.hpp"
#include "particles.hpp"

using namespace Particles;
using namespace EnergyProduction;


/**
 * This test will make sure that the sanity test
 * provided in the exercise text passes at all times.
 */
TEST(EnergyProduction, energy_sanity_test) {

  MassFractions MF;
  MF.X  = 0.7;
  MF.Y  = 0.29;
  MF.Y3 = 1e-10;
  MF.Y4 = MF.Y - MF.Y3;
  MF.Z  = 0.01;
  MF.Z_7Li = 1e-13;
  MF.Z_7Be = 1e-13;
  MF.setFractions();

  double T = 1.57e7;   // K
  double rho = 1.62e5; // kg m^-3
  arma::mat terms = arma::zeros<arma::mat>(N_PARTICLES, N_PARTICLES);

  double result = energy(T, rho, MF, terms) * rho;
  terms *= rho;

  auto eps = [] (double ans) {return 0.005*pow(10,(int)log10(ans));};

  EXPECT_NEAR(4.04e2, result, eps(1e2));
  EXPECT_NEAR(4.04e2, terms(_p,_p), eps(1e2));
  EXPECT_NEAR(1.94e-6, terms(_3He,_3He), eps(1e-6));
  EXPECT_NEAR(4.88e-05, terms(_3He,_4He), eps(1e-5));
  EXPECT_NEAR(1.53e-06, terms(_e,_7Be), eps(1e-6));
  EXPECT_NEAR(5.32e-4, terms(_p,_7Li), eps(1e-4));
}
