#include <cmath>
#include <iostream>

#include "constants.h"
#include "particles.h"
#include "reaction_energies.h"
#include "functions.h"
#include "massfractions.h"
#include "energy_production.h"

using namespace Particles;
using namespace Lambdas;
using namespace Reaction_energies;
using std::cout;
using std::endl;

double energy(double T, double rho, MassFractions fractions) {
  double epsilon = 0;
  double addon;
  for (int p1 = _e; p1 < N_PARTICLES; p1++) {
    for (int p2 = p1; p2 < N_PARTICLES; p2++) {
      addon = rate(Particle(p1), Particle(p2), fractions, T, rho) * Q[p1][p2];
      cout << "r_" << particle_names[p1] << particle_names[p2]
	   << " Q_" << particle_names[p1] << particle_names[p2]
	   << " rho = " << addon * rho << endl;
      epsilon += addon;
    }
  }
  return epsilon;
}

double rate(Particle p1, Particle p2, MassFractions fractions, double T, double rho) {
  return 1./ (rho * (1 + delta(p1, p2)))
    * lambda[p1][p2](T)
    * n_density(p1, fractions, rho)
    * n_density(p2, fractions, rho);
}


double n_density(Particle p, MassFractions fractions, double rho) {
  double n = 0;
  if (p == _e) {
    for (int i = _p; i < N_PARTICLES; i++)
      n += available_ionized_electrons[i] * n_density(Particle(i), fractions, rho);
  }
  else 
    n = fractions.fractions[p] * rho / (core_elements[p] * Constants::m_u);
  
  return n;
}
