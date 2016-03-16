#ifndef STATE_EQUATIONS_H
#define STATE_EQUATIONS_H

#include <cmath>
#include <functional>

#include "constants.h"
#include "particles.h"
#include "massfractions.h"

/**
 * Return the mean molecular weight.
 * @param mf Mass fractions for the star
 * @return mu_0 - the mean molecular weight [dim. less]
 */
double mu_0(MassFractions mf);

/**
 * Return the density
 * @param T Temperature [K]
 * @param P Pressure [kg s^-2 m^-1]
 * @param mu_0 Mean molecular weight [dim. less]
 * @return rho - density [kg m^-3]
 */
double rho(double T, double P, double mu_0);


/**
 * Return the pressure
 * @param T Temperature [K]
 * @param rho Density [kg m^-3]
 * @param mu_0 Mean molecular weight [dim. less]
 * @return P - pressure [kg s^-2 m^-1]
 */
double P(double T, double rho);

#endif
