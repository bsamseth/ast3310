#include <iostream>
#include <typeinfo>
#include <chrono>

#include "constants.h"
#include "particles.h"
#include "reaction_energies.h"
#include "functions.h"
#include "massfractions.h"
#include "energy_production.h"

using std::cout;
using std::endl;

using namespace Particles;
using namespace EnergyProduction;

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

  auto t1 = std::chrono::high_resolution_clock::now();
  
  double result = energy(T, rho, MF) * rho; 
  cout << "sum( r_ij * Q_ij * rho ) = "
       << result  << endl;

  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = t2 - t1;
  cout << "Execution time: " << duration.count()  << " ms"<< endl;
  
  return 0;
}
