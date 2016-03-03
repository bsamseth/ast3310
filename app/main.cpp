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

  for (int p = _e; p < N_PARTICLES; p++)
    cout << "Mass fraction of particle " << particle_names[p]
	 << " = " << MF[p] << endl;


  double T = 1.57e7;   // K
  double rho = 1.62e5; // kg m^-3

  
  cout << "Energy production with T = "
       << T << "K and density rho = "
       << rho << "kg m^-3 is: epsilon = " 
       << energy(T, rho, MF) << endl;
 
  cout << Lambdas::lambda[_p][_p](123) << endl;
  
  
  return 0;
}
