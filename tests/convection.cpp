#include <gtest/gtest.h>
#include <cmath>
#include <string>

#include "constants.hpp"
#include "state_equations.hpp"
#include "integrate.hpp"
#include "thirdordersolver.hpp"

TEST(Convection, sanity_test) {

    MassFractions MF;
    MF.X  = 0.7;
    MF.Y  = 0.29;
    MF.Y3 = 1e-10;
    MF.Y4 = MF.Y - MF.Y3;
    MF.Z  = 0.01;
    MF.Z_7Li = 1e-13;
    MF.Z_7Be = 1e-13;
    MF.setFractions();

    // use own mu, is about 0.618, ~3% different from 0.6
    double mu_0 = StateEquations::mu_0(MF);
    // use exercise kappa, own is about 6.
    // kappa tested, should not be indication of a bug
    double kappa = 3.98;
    double L = Constants::Sun::L;
    double T = 0.9e6;
    double rho = 55.9;
    double r = 0.84 * Constants::Sun::R;
    double m = 0.99 * Constants::Sun::M;
    double P = StateEquations::P(T, rho, mu_0);

    double nabla_radiative, nabla, F_C, F_R, dTdm;

    Integrate::calculate_convection(T, P, r, L, rho, m, mu_0,
                                    nabla_radiative, nabla,                        dTdm, F_C, F_R, kappa);

    EXPECT_NEAR(3.26, nabla_radiative, 0.005);
    EXPECT_NEAR(0.400001, nabla, 0.0000005);
    EXPECT_NEAR(0.88, F_C, 0.005);
    EXPECT_NEAR(0.12, F_R, 0.005);
    EXPECT_TRUE(Integrate::nabla_ad() < nabla && nabla < nabla_radiative);
}
