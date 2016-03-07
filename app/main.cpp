#include <iostream>
#include <typeinfo>
#include <iomanip>   // for std::setprecision
#include <chrono>
#include <armadillo>

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
  arma::mat terms = arma::zeros<arma::mat>(N_PARTICLES, N_PARTICLES);

  auto t1 = std::chrono::high_resolution_clock::now();

  double result = energy(T, rho, MF, terms) * rho; 
  for (int p1 = _e; p1 < N_PARTICLES; p1++) {
    for (int p2 = p1; p2 < N_PARTICLES; p2++) {
      if (terms(p1,p2) != 0)
	cout << std::scientific << std::setprecision(2)
	     << "r_" << particle_name[p1] << particle_name[p2]
	     << " Q_" << particle_name[p1] << particle_name[p2]
	     << " rho = " << terms(p1,p2) * rho << '\n';
    }
  }
  cout << "epsilon * rho = " << result << '\n';
  
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = t2 - t1;
  cout << "Execution time: " << duration.count()  << " ms"<< endl;
  
  return 0;
}
