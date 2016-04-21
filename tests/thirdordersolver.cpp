#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

#include "thirdordersolver.hpp"

const double eps = 1e-6;


/**
 * Expect 1 solution for x^3 - 3^3 = 0
 */
TEST(Third_order_solver, trivial) {

    double* x = new double[3];

    int n = solve3order(x, 1, 0, 0, -27);

    EXPECT_EQ(1, n);
    EXPECT_EQ(3, x[0]);
}

/**
 * Expect 1 solution for
 * x^3 + x^2 + x + 1 = 0.
 * Solutions are x = 1, x = +- i
 */
TEST(Third_order_solver, all_ones) {
    double* x = new double[3];

    int n = solve3order(x, 1, 1, 1, 1);

    EXPECT_EQ(1, n);
    EXPECT_NEAR(-1, x[0], eps);
    EXPECT_NEAR(0, x[1], eps);
    EXPECT_NEAR(1, std::abs(x[2]), eps);
}


/**
 * Expect 1 real solution for x^3 + 2x + 2 = 0
 * with two complex conjugate solutions
 * x = 0.3855 +- 1.5639 i
 */
TEST(Third_order_solver, no_quad_term) {
    double* x = new double[3];

    int n = solve3order(x, 1, 0, 2, 2);

    EXPECT_EQ(1, n);
    EXPECT_NEAR(-0.770916997059248, x[0], eps);
    EXPECT_NEAR(0.3854585, x[1], eps);
    EXPECT_NEAR(1.56388451, std::abs(x[2]), eps);
}


TEST(Third_order_solver, no_linear_term) {
    double* x = new double[3];

    int n = solve3order(x, 1, 2, 0, 2);

    EXPECT_EQ(1, n);
    EXPECT_NEAR(-2.35930409, x[0], eps);
    EXPECT_NEAR(0.17965204, x[1], eps);
    EXPECT_NEAR(0.90301315, std::abs(x[2]), eps);
}

/**
 * Expect 3 solutions for
 * 13/3 (x - 3/4) (x + 7/8) (x - 9) =
 * 13/3 x^3 - 923/24 x^2 - 247/32 x + 819/32 = 0.
 */
TEST(Third_order_solver, three_real_roots) {
    double* x = new double[3];

    int n = solve3order(x, 13./3, -923./24, -247./32, 819./32);

    EXPECT_EQ(3, n);

    double expected [3] = {3./4, -7./8, 9};
    for (int i = 0; i < 3; i++) {
        bool success = false;
        for (int j = 0; j < 3; j++) {
            success |= std::abs(expected[j] - x[i]) < eps;
        }
        EXPECT_TRUE(success) << "No match for root #" << i
                             << ": " << x[i] << ".\n";
    }
}
