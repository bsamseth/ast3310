#ifndef MASSFRACTIONS_H
#define MASSFRACTIONS_H

#include "constants.h"

struct MassFractions {
  double X;
  double Y3;
  double Y4;
  double Y;
  double Z;
  double Z_7Li;
  double Z_7Be;
  double fractions [Particles::N_PARTICLES] = { 0 };

  void setFractions() {
    fractions[Particles::_e]   = 0;
    fractions[Particles::_p]   = X;
    fractions[Particles::_3He] = Y3;
    fractions[Particles::_4He] = Y4;
    fractions[Particles::_7Li] = Z_7Li;
    fractions[Particles::_7Be] = Z_7Be;
  }

  double operator[] (Particles::Particle p) {
    return fractions[p];
  }

  double operator[] (int i) {
    return fractions[i];
  }
};


#endif
