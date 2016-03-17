#ifndef INTEGRATE_H
#define INTEGRATE_H

#include <sstream>
#include "massfractions.h"

namespace Integrate {
  std::stringstream integrate(double L_0, double T_0, double P_0, double rho_0, double M_0, double R_0, MassFractions MF, double dm);
}

#endif
