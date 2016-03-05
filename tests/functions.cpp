#include <gtest/gtest.h>
#include <cmath>

#include "functions.h"
#include "particles.h"
#include "constants.h"

using namespace Particles;
using namespace Lambdas;

const double eps = 1e-6;

TEST(Functions, deltas) {
  EXPECT_EQ(1, delta(123,123));
  EXPECT_EQ(0, delta(1,2));
  EXPECT_EQ(1, delta(_3He,_3He));
  EXPECT_EQ(0, delta(_3He,_4He));
}

TEST(Functions, lambda_pp) {
  double T9 = 1.57e7 * 1e-9; // Mega Kelvin
  double N_A_lambda = 4.01e-15 * pow(T9,-2./3) * exp(-3.380*pow(T9,-1./3)) 
    * (1 + 0.123*pow(T9,1./3) + 1.09*pow(T9,2./3) + 0.938*T9  );
  double l =  N_A_lambda / Constants::N_A / 1e6;
  EXPECT_NEAR(l, lambda[_p][_p](T9*1e9), l*eps);
}


TEST(Functions, lambda_33) {
  double T9 = 1.57e7 * 1e-9; // Mega Kelvin
  double N_A_lambda = 6.04e10*pow(T9, -2./3)*exp(-12.276*pow(T9,-1./3)) *
    (1 + 0.034*pow(T9,1./3) - 0.522*pow(T9,2./3) - 0.124*T9 + 0.353*pow(T9,4./3) + 0.213*pow(T9,-5./3));
  double l =  N_A_lambda / Constants::N_A * Constants::M3_PER_CM3;
  EXPECT_NEAR(l, lambda[_3He][_3He](T9*1e9), l*eps);
}

TEST(Functions, lambda_34) {
  double T9 = 1.57e7 * 1e-9; // Mega Kelvin
  double T9_star = T9 / (1 + 4.95e-2 * T9);
  double N_A_lambda = 5.61e6*pow(T9_star, 5./6)*pow(T9,-3./2)*exp(-12.826*pow(T9_star,-1./3));
  double l =  N_A_lambda / Constants::N_A / 1e6;
  EXPECT_NEAR(l, lambda[_3He][_4He](T9*1e9), l*eps);
}

TEST(Functions, lambda_e7Be) {
  double T9 = 1.57e7 * 1e-9; // Mega Kelvin
  double N_A_lambda = 1.34e-10*pow(T9,-1./2)*
    (1 - 0.537*pow(T9,1./3) + 3.86*pow(T9,2./3) + 0.0027/T9*exp(2.515e-3/T9));
  double l =  N_A_lambda / Constants::N_A / 1e6;
  EXPECT_NEAR(l, lambda[_e][_7Be](T9*1e9), l*eps);
}

TEST(Functions, lambda_p7Li) {
  double T9 = 1.57e7 * 1e-9; // Mega Kelvin
  double T9_star = T9 / (1 + 0.759*T9);
  double N_A_lambda = 1.096e9*pow(T9,-2./3)*exp(-8.472*pow(T9,-1./3))
    - 4.830e8 * pow(T9_star,5./6)*pow(T9,-3./2)*exp(-8.472*pow(T9_star,-1./3))
    + 1.06e10*pow(T9,-3./2)*exp(-30.442/T9);
  double l =  N_A_lambda / Constants::N_A / 1e6;
  EXPECT_NEAR(l, lambda[_p][_7Li](T9*1e9), l*eps);
}
