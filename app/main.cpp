#include <iostream>
#include <typeinfo>

#include "constants.h"
#include "particles.h"
#include "reaction_energies.h"
#include "functions.h"
#include "massfractions.h"
#include "energy_production.h"

using std::cout;
using std::endl;

using namespace Particles;

int main() {

  MassFractions MF;
  MF.X  = 0.7;
  MF.Y  = 0.29;
  MF.Y3 = 1e-10;
  MF.Y4 = MF.Y - MF.Y3;
  MF.Z  = 0.01;
  MF.Z_7Li = 1e-13;
  MF.Z_7Be = 1e-13;
  MF.setFractions();

  double T = 1.57e7;   // K
  double rho = 1.62e5; // kg m^-3

  double result = energy(T, rho, MF) * rho; 
  cout << "sum( r_ij * Q_ij * rho ) = "
       << result  << endl;
  
  return 0;
}
