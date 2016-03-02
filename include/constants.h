#ifndef CONSTANTS_H
#define CONSTANTS_H

// #include "functions.h"


namespace Constants {
  const double JOULES_PER_MEV = 1.6022e-13; // J/MeV
  const double c = 299792458;               // m/s
  
}

inline double MeV_to_Joules(double MeV) {
  return MeV * Constants::JOULES_PER_MEV;
}

namespace Particles {
  enum Particle {
    e, p, _3He, _4He, _7Li, _7Be, N_PARTICLES
  };
}


namespace Reactions {
  enum Reaction {
    _pp, _33, _34, _p7Li, _e7Be, N_REACTIONS
  };
}

namespace Reaction_energies {
  const double Q_pp = MeV_to_Joules(0.15 + 5.49 + 1.02); // combined first two steps
  const double Q_33 = MeV_to_Joules(12.86);
  const double Q_34 = MeV_to_Joules(1.59);
  const double Q_e7Be = MeV_to_Joules(0.05);
  const double Q_p7Li = MeV_to_Joules(17.35);
  const double Q [Reactions::N_REACTIONS] = {Q_pp,
					     Q_33,
					     Q_34,
					     Q_p7Li,
					     Q_e7Be };
}





#endif
