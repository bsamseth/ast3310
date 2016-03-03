#ifndef REACTION_ENERGIES_H
#define REACTION_ENERGIES_H


#include "constants.h"
#include "particles.h"

namespace Reaction_energies {
  const double Q_pp = MeV_to_Joules(0.15 + 5.49 + 1.02); // combined first two steps
  const double Q_33 = MeV_to_Joules(12.86);
  const double Q_34 = MeV_to_Joules(1.59);
  const double Q_e7Be = MeV_to_Joules(0.05);
  const double Q_p7Li = MeV_to_Joules(17.35);

  /*
   * Q_ij are to be accessed by 2D array Q. For instance, Q[_3He][_3He] -> Q_33
   * To avoid counting reactions two times, we have Q_ij != 0 -> Q_ji = 0.
   * Smallest particle should be used as first index (if not, then zero will be the value)
   * In other words, the matrix Q_ij is upper triangular. 
   */
  const double Q [Particles::N_PARTICLES][Particles::N_PARTICLES] = {
    { 0, 0   , 0   , 0   , 0     , Q_e7Be },  // e
    { 0, Q_pp, 0   , 0   , Q_p7Li, 0      }, // p
    { 0, 0   , Q_33, Q_34, 0     , 0      }, // 3He
    { 0, 0   , 0   , 0   , 0     , 0      }, // 4He, included in 3He
    { 0, 0   , 0   , 0   , 0     , 0      }, // _7Li, included in p
    { 0, 0   , 0   , 0   , 0     , 0      }// _7Be, included in e
  }; 
}

#endif
