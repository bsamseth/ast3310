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

TEST (Opacity, sanity_please) {

  double log10T_wanted_array [] = {3.75,3.755,3.755,3.755,3.755,3.770,3.780,3.795,3.770,3.775,3.780,3.795,3.80};
  double log10R_wanted_array [] = {-6.0,-5.95, -5.80, -5.70, -5.55,-5.95,-5.95,-5.95,-5.8,-5.75,-5.70,-5.55,-5.5};

  cout << std::scientific;

  for (int i = 0; i < 13; i++) {
    double log10R_wanted = log10R_wanted_array[i];
    double log10T_wanted = log10T_wanted_array[i];
    double T = pow(10, log10T_wanted);
    double rho = Constants::KG_M3_per_G_CM3 * pow((T*1e-6), 3) * pow(10, log10R_wanted);
    cout << "Input logT = " << log10(T) << ", rho(SI) = " << rho << " -> kappa = " << opacity(T, rho) << '\n';
  }

  double T = 5.7e6;
  double rho = 5.1*1.408e3;
  cout << "Input logT = " << log10(T) << ", rho(SI) = " << rho << " -> kappa = " << opacity(T, rho) << '\n';

  EXPECT_EQ(1,0);
  
}
