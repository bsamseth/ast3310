#ifndef ENERGY_PRODUCTION_H
#define ENERGY_PRODUCTION_H

#include "constants.h"
#include "particles.h"
#include "massfractions.h"
#include "functions.h"

/**
 * Functions related to energy production.
 */
namespace EnergyProduction {
  
  /**
   * Accept a temperature and a density, and return the energy
   * in Joules produced by the PPI and PPII cycles,
   * per mass per second [J kg^-1 s^-1].
   *
   * The mass fractions for X, Y_3 etc. must also be specified.
   *
   * @param T Temperature
   * @param rho Density
   * @param fractions MassFractions object containing all mass fractions
   * @return Total energy produced by PPI and PPII [J kg^-1 s^-1]
   */
  double energy(double T, double rho, MassFractions fractions);

  /**
   * Return the reaction rate r_ij [kg^-1 s^-1] for a
   * given reaction, mass fractions and density.
   *
   * @param particle1 First particle of reaction
   * @param particle2 Second particle of reaction
   * @param fractions MassFractions object containing all mass fractions
   * @param T Temperature
   * @param rho Density
   * @return Rate of reaction [kg^-1 s^-1]
   */
  double rate(Particles::Particle particle1, Particles::Particle particle2, MassFractions fractions, double T, double rho);

  /**
   * Return n_i = fraction[i] * rho / k m_u
   * where k is the number of elements in the core of particle i.
   * 
   * @param p Particle to compute number density of
   * @param fractions MassFractions object containing all mass fractions
   * @param rho Density
   * @return Number density of particle p [m^-3]
   */
  double n_density(Particles::Particle p, MassFractions fractions, double rho);
}

#endif
