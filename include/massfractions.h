#ifndef MASSFRACTIONS_H
#define MASSFRACTIONS_H

#include "constants.h"
#include "particles.h"

/**
 * Structure for keeping track of all mass fractions in the star.
 *
 * Fields for every relevant particle should be present, including
 * Y (Y3 + Y4) and Z for all metals. The structure can be indexed by particle.
 */
struct MassFractions {
  double X;
  double Y3;
  double Y4;
  double Y;
  double Z;
  double Z_7Li;
  double Z_7Be;
  double fractions [Particles::N_PARTICLES] = { 0 };

  /**
   * Updates the fractions array to hold the current values
   * of field values
   */
  void setFractions() {
    fractions[Particles::_e]   = 0;
    fractions[Particles::_p]   = X;
    fractions[Particles::_3He] = Y3;
    fractions[Particles::_4He] = Y4;
    fractions[Particles::_7Li] = Z_7Li;
    fractions[Particles::_7Be] = Z_7Be;
  }

  /**
   * Return fraction corresponding to the particle
   * @param p particle to get fraction for
   * @return fraction corresponding to particle
   */
  double operator[] (Particles::Particle p) {
    return fractions[p];
  }

  double operator[] (int i) {
    return fractions[i];
  }
};


#endif
