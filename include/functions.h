#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <functional>

#include "constants.h"
#include "particles.h"


inline int delta(int i, int j) {
  return (int) i == j;
}

inline int delta(Particles::Particle i, Particles::Particle j) {
  return (int) i == j;
}

namespace Lambdas {

  
  extern std::function<double(double)> lambda_pp;
  extern std::function<double(double)> lambda_33;;
  extern std::function<double(double)> lambda_34;
  extern std::function<double(double)> lambda_e7Be;
  extern std::function<double(double)> lambda_p7Li;
  extern std::function<double(double)> zero;

  /*
   * lambda_ij are to be accessed by 2D array lambda. For instance, lambda[_3He][_3He] -> lambda_33
   * To avoid counting reactions two times, we have lambda_ij != 0 -> lambda_ji = 0. (lambda(x)=0)
   * Smallest particle should be used as first index (if not, then zero will be the value)
   * In other words, the matrix lambda_ij is upper triangular. 
   */
  extern std::function<double(double)> lambda [Particles::N_PARTICLES][Particles::N_PARTICLES];
}


#endif
