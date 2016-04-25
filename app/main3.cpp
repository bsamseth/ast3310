#include <iostream>
#include <fstream>
#include <typeinfo>
#include <iomanip>   // for std::setprecision
#include <string>
#include <chrono>
#include <armadillo>

#include "constants.hpp"
#include "particles.hpp"
#include "reaction_energies.hpp"
#include "functions.hpp"
#include "massfractions.hpp"
#include "energy_production.hpp"
#include "integrate.hpp"
#include "state_equations.hpp"

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
  bool setP = false;

  if (argc > 4) {
    R_scale = std::atof(args[1]);
    M_scale = std::atof(args[2]);
    rho_scale = std::atof(args[3]);
    T_scale = std::atof(args[4]);
    if (argc > 5)
      dm_scale = std::atof(args[5]);
    if (argc > 6)
      filename = args[6];

    if (argc > 7)
      setP = true;
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

  double L_0   = 1 * Sun::L;
  double R_0   = 1 * Sun::R * R_scale;
  double M_0   = 1 * Sun::M * M_scale;
  double rho_0 = 1.42e-7 * Sun::rho * rho_scale;
  double T_0   = 5770 * T_scale;
  double P_0   = StateEquations::P(T_0, rho_0, StateEquations::mu_0(MF));
  if (setP) {
    /*
     * If setP is true, then rho_scale is interpreted as P_scale.
     * P is then scaled accoriding to the the value that P would have with
     * rho_scale = 1 (and T_scale whatever is used).
     */
    rho_0 = 5.1  * Sun::rho;
    P_0 = StateEquations::P(T_0, rho_0, StateEquations::mu_0(MF)) * rho_scale;
    rho_0 = StateEquations::rho(T_0, P_0, StateEquations::mu_0(MF));
  }

  double dm = (dm_scale == 0) ? 0 : - M_0/dm_scale;

  std::string ss = Integrate::integrate_conv(L_0, T_0, P_0,
					      rho_0, M_0, R_0,
					      MF, dm);

  std::ofstream outfile (filename);
  outfile << ss;
  outfile.close();

  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = t2 - t1;
  cout << "# Execution time: " << duration.count() * 1e-3  << " s"<< endl;

  return 0;
}
