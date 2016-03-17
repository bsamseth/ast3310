#include <iostream>
#include <fstream>
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
#include "integrate.h"
#include "state_equations.h"

using std::cout;
using std::endl;

using namespace Particles;
using namespace EnergyProduction;
using namespace Constants;

int main() {
  arma::mat terms = arma::zeros<arma::mat>(N_PARTICLES, N_PARTICLES);
  auto t1 = std::chrono::high_resolution_clock::now();

  MassFractions MF;
  MF.X  = 0.7;
  MF.Y  = 0.29;
  MF.Y3 = 1e-10;
  MF.Y4 = MF.Y - MF.Y3;
  MF.Z  = 0.01;
  MF.Z_7Li = 1e-13;
  MF.Z_7Be = 1e-13;
  MF.setFractions();

  
  double L_0   = 1.0  * Sun::L;
  double R_0   = 0.72 * Sun::R;
  double M_0   = 1.0  * Sun::M;
  double rho_0 = 5.1  * Sun::rho;
  double T_0   = 5.7e6;
  double P_0   = StateEquations::P(T_0, rho_0, StateEquations::mu_0(MF));

  double dm = - M_0/10000;
  
  std::stringstream ss = Integrate::integrate(L_0, T_0, P_0,
					      rho_0, M_0, R_0,
					      MF, dm);
  
  std::ofstream outfile ("output.dat");
  outfile << ss.str();
  outfile.close();
  
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = t2 - t1;
  cout << "# Execution time: " << duration.count()  << " ms"<< endl;
  
  return 0;
}
