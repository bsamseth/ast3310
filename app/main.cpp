#include <iostream>
#include <fstream>
#include <typeinfo>
#include <iomanip>   // for std::setprecision
#include <string>
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
using std::string;

using namespace Particles;
using namespace EnergyProduction;
using namespace Constants;

int main(int argc, char** args) {
  double R_scale=1, M_scale=1, rho_scale=1, T_scale=1;
  double dm_scale = 0; // dm = M0/dm_scale
  string filename = "output.dat";
  

  if (argc > 4) {
    R_scale = std::atof(args[1]);
    M_scale = std::atof(args[2]);
    rho_scale = std::atof(args[3]);
    T_scale = std::atof(args[4]);
    if (argc > 5)
      dm_scale = std::atof(args[5]);
    if (argc > 6)
      filename = args[6];
	
  } else {
    cout << "Usage: " << args[0]
	 << " R_scale M_scale rho_scale T_scale"
	 << " [dm_scale] [outputfile]"
	 << endl;
    exit(0);
  }
  
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

  double L_0   = 1  * Sun::L;
  double R_0   = 0.72 * Sun::R * R_scale;
  double M_0   = 1  * Sun::M * M_scale;
  double rho_0 = 5.1  * Sun::rho * rho_scale;
  double T_0   = 5.7e6 * T_scale;
  double P_0   = StateEquations::P(T_0, rho_0, StateEquations::mu_0(MF));

  double dm = (dm_scale == 0) ? 0 : - M_0/dm_scale;
  //double dm = 0; // use dss
  
  std::string ss = Integrate::integrate(L_0, T_0, P_0,
					      rho_0, M_0, R_0,
					      MF, dm);
  
  std::ofstream outfile (filename);
  outfile << ss;
  outfile.close();
  
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = t2 - t1;
  //cout << "# Execution time: " << duration.count() * 1e-3  << " s"<< endl;
  
  return 0;
}
