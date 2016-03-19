#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

/**
 * Namespace containing various mathematical constants.
 */
namespace Constants {
  const double JOULES_PER_MEV = 1.6022e-13; ///< J/MeV
  const double M3_PER_CM3 = 1e-6;           ///< m^3 / cm^3
  const double KG_M3_per_G_CM3 = 1e3;       ///< kg/m^3 / g/cm^3
  const double M2_KG_PER_CM2_G = 0.1;       ///< m^2/kg / cm^2/g
  const double c = 299792458;               ///< m/s
  const double m_u = 1.6605e-27;            ///< J
  const double N_A = 6.0221409e23;          ///< dim. less
  const double k_b = 1.38064852e-23;        ///< m^2 kg s^-2 K^-1
  const double G = 6.67408e-11;             ///< m^3 kg^-1 s^-2
  const double pi = 3.14159265359;          ///< dim. less
  const double sigma = 5.670367e-8;         ///< W m^-2 K^-4
  const double a = 4*sigma/c;               ///< kg m^-2 s^-1
  
  namespace Sun {
    const double L = 3.846e26;              ///< W
    const double M = 1.989e30;              ///< kg
    const double R = 6.96e8;                ///< m
    const double rho = 1.408e3;             ///< kg m^-3
    const double t_life = 4.57e9;           ///< years
    const double kappa = 1.0;               ///< m^2 kg^-1

    namespace Core {
      const double rho = 1.62e5;            ///< kg m^-3
      const double T = 1.57e7;              ///< K
      const double P = 3.45e16;             ///< Pa
    }
  }
}

inline double MeV_to_Joules(double MeV) {
  return MeV * Constants::JOULES_PER_MEV;
}


#endif
