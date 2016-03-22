#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>

#include "particles.h"
#include "constants.h"
#include "state_equations.h"
#include "massfractions.h"
#include "opacity.h"

using std::cout;
using std::endl;
using namespace Particles;
//using namespace StateEquations;

const double eps = 1e-13;

TEST (Opacity, interpolation) {

  double log10T_wanted_array [] = {3.75,3.755,3.755,3.755,3.755,3.770,3.780,3.795,3.770,3.775,3.780,3.795,3.80};
  double log10R_wanted_array [] = {-6.0,-5.95, -5.80, -5.70, -5.55,-5.95,-5.95,-5.95,-5.8,-5.75,-5.70,-5.55,-5.5};
  double expected_result [] = {2.84e-3,3.10e-3,2.68e-3,2.46e-3,2.12e-3,4.70e-3,6.25e-3,9.45e-3,4.05e-3,4.43e-3,4.94e-3,6.89e-3,7.69e-3};
  
  cout << std::scientific << std::setprecision(2);

  Opacity kappa;

  for (int i = 0; i < 13; i++) {
    double lT = log10T_wanted_array[i];
    double lR = log10R_wanted_array[i];
    double T = pow(10, lT);
    double rho = pow((T*1e-6),3) * pow(10, lR) * 1e3;

    EXPECT_NEAR(expected_result[i], kappa(T,rho), 0.15e-3);
    
    // cout << "log(T)=" << lT << ", log(R)=" << lR
    // 	 << " (rho=" << rho << ") -> "
    // 	 << opacity(T,rho) << '\n';
  }
}
