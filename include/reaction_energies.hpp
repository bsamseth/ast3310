#ifndef REACTION_ENERGIES_H
#define REACTION_ENERGIES_H


#include "constants.hpp"
#include "particles.hpp"

/**
 * Namespace for energies produced by all relevant reactions in the star.
 */
namespace ReactionEnergies {

  const double Q_pp = Constants::JOULES_PER_MEV * (0.15 + 5.49 + 1.02); // combined first two steps
  const double Q_33 = Constants::JOULES_PER_MEV * (12.86);
  const double Q_34 = Constants::JOULES_PER_MEV * (1.59);
  const double Q_e7Be = Constants::JOULES_PER_MEV * (0.05);
  const double Q_p7Li = Constants::JOULES_PER_MEV * (17.35);

  /**
   * Q_ij are to be accessed by 2D array Q. For instance, Q[_3He][_3He] -> Q_33. <br>
   * To avoid counting reactions two times, we have Q_ij != 0 -> Q_ji = 0. <br>
   * Smallest particle should be used as first index (if not, then zero will be the value). <br>
   * In other words, the matrix Q_ij is upper triangular (and sparse).
   */
  const double Q [Particles::N_PARTICLES][Particles::N_PARTICLES] = {
    { 0, 0   , 0   , 0   , 0     , Q_e7Be }, // e
    { 0, Q_pp, 0   , 0   , Q_p7Li, 0      }, // p
    { 0, 0   , Q_33, Q_34, 0     , 0      }, // 3He
    { 0, 0   , 0   , 0   , 0     , 0      }, // 4He, included in 3He
    { 0, 0   , 0   , 0   , 0     , 0      }, // _7Li, included in p
    { 0, 0   , 0   , 0   , 0     , 0      }  // _7Be, included in e
  };
}

#endif
