#ifndef ENERGY_PRODUCTION_H
#define ENERGY_PRODUCTION_H

#include "constants.h"
#include "particles.h"
#include "massfractions.h"
#include "functions.h"

/*
 * Method that accepts a temperature and a density,
 * and returns the energi in Joules produced by the PPI and PPII cycles,
 * per mass per second [J kg^-1 s^-1].
 *
 * The mass fractions for X, Y_3 etc. must also be specified.
 */
double energy(double T, double rho, MassFractions fractions);

/*
 * Method that returns the reaction rate r_ij [kg^-1 s^-1] for a
 * given reaction, mass fractions and density. 
 */
double rate(Particles::Particle particle1, Particles::Particle particle2, MassFractions fractions, double T, double rho);

/*
 * Returns n_i = fraction[i] * rho / k m_u
 * where k is the number of elements in the core of particle i.
 */
double n_density(Particles::Particle p, MassFractions fractions, double rho);


#endif
