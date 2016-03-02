#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <functional>
#include "constants.h"

inline int delta(int i, int k) {
  return (int) i == k;
}

namespace Lambdas {

  double lambda_pp(double T) {
    double T9 = T * 1e-9;
    return 4.01e-15 * pow(T9,-2./3) * exp(-3.380*pow(T9, -1./3)) *
      (1 + 0.123*pow(T9, 1./3) + 1.09* pow(T9, 2./3) + 0.938*T9 );
  }

  double lambda_33(double T) {
    double T9 = T * 1e-9;
    return 6.04e10 * pow(T9, -2./3) * exp(-12.276 * pow(T9, -1./3)) *
      (1 + 0.034 * pow(T9, 1./3) - 0.522 * pow(T9, 2./3) - 0.124 * T9 +
       0.353 * pow(T9, 4./3) + 0.213 * pow(T9, -5./3));
  }

  double lambda_34(double T) {
    double T9 = T * 1e-9;
    double T9_star = T9 / (1 + 4.95e-2*T9);
    return 5.61e6 * pow(T9_star, 5./6) * pow(T9, -3./2) *
      exp(-12.826 * pow(T9_star, -1./3));
  }

  double lambda_e7Be(double T) {
    double T9 = T * 1e-9;
    return 1.34e-10 * pow(T9,-1./2) * (1 - 0.537 * pow(T9, 1./3) +
				       3.86 * pow(T9, 2./3) +
				       0.0027 / T9 * exp(2.515e-3/T9));
  }

  double lambda_p7Li(double T) {
    double T9 = T * 1e-9;
    double T9_star = T9 / (1 + 0.0759*T9);
    return 1.096e9 * pow(T9, -2./3) * exp(-8.472 * pow(T9, -1./3)) -
      4.830e8 * pow(T9_star, 5./6) * pow(T9, -3./2) * exp(-8.479 * pow(T9_star, -1./3)) +
      1.06e10 * pow(T9, -3./2) * exp(-30.442/T9);
  }

  /*
  double lambda_p7Be(double T) {
    double T9 = T * 1e-9;
    return 3.11e5 * pow(T9, -2./3) * exp(-10.262 * pow(T9, -1./3)) +
      2.53e3 * pow(T9, -3./2) * exp(-7.306/T9);
  }
  */

  const std::function<double(double)> lambda [Reactions::N_REACTIONS] = {lambda_pp,
									 lambda_33,
									 lambda_34,
									 lambda_p7Li,
									 lambda_e7Be };
}


#endif
