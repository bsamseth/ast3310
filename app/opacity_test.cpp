#include <iostream>
#include <typeinfo>
#include <iomanip>   // for std::setprecision
#include <chrono>
#include <armadillo>

#include "opacity.h"

using std::cout;
using std::endl;

int main() {

  double log10T_wanted_array [] = {3.75,3.755,3.755,3.755,3.755,3.770,3.780,3.795,3.770,3.775,3.780,3.795,3.80};
  double log10R_wanted_array [] = {-6.0,-5.95, -5.80, -5.70, -5.55,-5.95,-5.95,-5.95,-5.8,-5.75,-5.70,-5.55,-5.5};


  // for (int i = 0; i < 13; i++) {
  //   double log10R_wanted = log10R_wanted_array[i];
  //   double log10T_wanted = log10T_wanted_array[i];
  //   double T = pow(10, log10T_wanted);
  //   double rho = pow(T*1e-6,3) * pow(10,log10R_wanted);
  //   opacity(T, rho);
  // }

  double log10R_wanted = log10R_wanted_array[1];
  double log10T_wanted = log10T_wanted_array[1];
  double T = pow(10, log10T_wanted);
  double rho = pow(T*1e-6,3) * pow(10,log10R_wanted);
  opacity(T, rho);
  return 0;
}
