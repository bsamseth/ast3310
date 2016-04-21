#include <cmath>
#include <iostream>
#include <algorithm> // for std::min
#include <armadillo>

#include "constants.hpp"
#include "particles.hpp"
#include "reaction_energies.hpp"
#include "functions.hpp"
#include "massfractions.hpp"
#include "energy_production.hpp"

using namespace Particles;
using namespace Lambdas;
using namespace ReactionEnergies;
using std::cout;
using std::endl;
using std::min;

namespace EnergyProduction {

  double energy(double T, double rho, MassFractions fractions, arma::mat& terms) {
    double epsilon = 0;
    double addon;
    for (int p1 = _e; p1 < N_PARTICLES; p1++) {
      for (int p2 = p1; p2 < N_PARTICLES; p2++) {
	addon = rate(Particle(p1), Particle(p2), fractions, T, rho) * Q[p1][p2];
	terms(p1,p2) = addon;
	epsilon += addon;
      }
    }
    return epsilon;
  }

  /**
   * Return the rate without considering rates of reactants (helper for rate(...))
   */
  double rate_simple(Particle p1, Particle p2, MassFractions fractions, double T, double rho) {
    return  1./ (rho * (1 + delta(p1, p2)))
      * lambda[p1][p2](T)
      * n_density(p1, fractions, rho)
      * n_density(p2, fractions, rho);
  }


  double rate(Particle p1, Particle p2, MassFractions fractions, double T, double rho) {
    double r = rate_simple(p1,p2,fractions,T,rho);

    /* Here we will say that no step can happen more often than
     * the step(s) that produced the reactant(s)
     */
    if (p1 == _3He) {
      // This I don't know if it's right, so I don't change anything
      // Passes sanity check, so I will assume/hope it works elsewhere as well
      double pp = rate_simple(_p,_p,fractions,T,rho);
      double _33 = rate_simple(_3He,_3He,fractions,T,rho);
      double _34 = rate_simple(_3He,_4He,fractions,T,rho);
      double scale = min (pp / (2*_33 + _34) , 1.0);
      r *= scale;

    } else if ( p1 == _e and p2 == _7Be) {
      // r_e7Be <= r_34
      r = min ( r, rate(_3He, _4He, fractions, T, rho) );
    } else if ( p1 == _p and p2 == _7Li) {
      // r_p7Li <= r_e7Be
      r = min ( r, rate(_e, _7Be, fractions, T, rho) );
    }

    return r;
  }


  double n_density(Particle p, MassFractions fractions, double rho) {
    double n = 0;
    if (p == _e) {
      for (int i = _p; i < N_PARTICLES; i++)
	n += available_ionized_electrons[i] * n_density(Particle(i), fractions, rho);
    }
    else
      n = fractions[p] * rho / (core_elements[p] * Constants::m_u);

    return n;
  }
}
