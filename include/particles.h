#ifndef PARTICLES_H
#define PARTICLES_H

#include <string>

namespace Particles {

  enum Particle {
    _e, _p, _3He, _4He, _7Li, _7Be, N_PARTICLES
  };

  const int core_elements [N_PARTICLES] = {0, 1, 2, 2, 3, 4};
  const int available_ionized_electrons [N_PARTICLES] = {0, 1, 2, 2, 0, 0}; // metals don't contribute
  const std::string particle_names [N_PARTICLES] = {"e", "p", "3He", "4He", "7Li", "7Be"};
}


#endif
