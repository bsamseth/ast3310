#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>


namespace Constants {
  const double JOULES_PER_MEV = 1.6022e-13; // J/MeV
  const double c = 299792458;               // m/s
  const double m_u = 1.6605e-27;            // J
  const double N_A = 6.0221409e23;
}

inline double MeV_to_Joules(double MeV) {
  return MeV * Constants::JOULES_PER_MEV;
}


#endif
