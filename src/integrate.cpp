
#include <sstream>
#include <iostream>
#include <armadillo>
#include <cmath>
#include <algorithm>
#include <string>

#include "particles.hpp"
#include "constants.hpp"
#include "energy_production.hpp"
#include "massfractions.hpp"
#include "state_equations.hpp"
#include "integrate.hpp"
#include "opacity.hpp"
#include "thirdordersolver.hpp"


using namespace Constants;
using namespace Particles;
using namespace Integrate;
using EnergyProduction::energy;
using std::abs;
using std::min;
using std::min_element;


void Integrate::calculate_convection(double T, double P, double r, double L,
                                     double rho, double m, double mu_0,
                                     double& nabla_radiative, double& nabla,
                                     double& dTdm, double& F_C,
                                     double& F_R, Opacity& kappa) {

    nabla_radiative = nabla_rad(T, rho, L, P, m, kappa);
    if (nabla_radiative > nabla_ad()) {
        double alpha = 1.0; // parameter, should be arond 1.
        double H_p = P * r*r / (rho * G * m);
        double l_m = alpha * H_p;
        double delta = 1; // - dln rho / dln T = 1, ideal gass
        double c_p = 5./2 * k_b / (mu_0* m_u);
        double g = G * m / (r*r);

        double U = 64 * sigma * T*T*T / (3 * kappa(T, rho) * rho*rho * c_p)
        * sqrt(H_p / (g * delta));

        double xi;
        {
            double U_lm2 = U / (l_m*l_m);
            double K = 4 / (l_m*l_m);
            double a = 1;
            double b = U_lm2;
            double c = U_lm2 * U * K;
            double d = - U_lm2 * (nabla_radiative - nabla_ad());
            double* x = new double[3];
            solve3order(x, a, b, c, d);
            xi = x[0];
            nabla = xi*xi + U*K * xi + nabla_ad();
        }

        double F_C_abs = rho * c_p * T * sqrt(g*delta) * pow(H_p, -3./2)
                            * pow(l_m/2., 2) * pow(xi, 3);
        double F_R_abs = 16 * Constants::sigma * Constants::G * T*T*T*T * m
                            / (3 * kappa(T, rho) * P * r*r) * nabla;

        F_C = F_C_abs / (F_C_abs + F_R_abs);
        F_R = F_R_abs / (F_C_abs + F_R_abs);

        dTdm = - T * G * m / (4 * pi * r*r*r*r * P) * nabla;
    }
    else {
        F_C = 0;
        F_R = 1;
        nabla = nabla_radiative;
    }
}

std::string Integrate::integrate_conv(double L_0, double T_0, double P_0, double rho_0, double M_0, double R_0, MassFractions MF, double dm) {
    std::stringstream ss;
    ss << "# m \t r \t P \t L \t T \t rho \t epsilon \t "
       << "F_C \t eps_PPI \t nabla \t nabla_rad\n";

    arma::mat energy_terms (N_PARTICLES, N_PARTICLES);

    double r = R_0, T = T_0, L = L_0, P = P_0, rho = rho_0, m = M_0, eps;;
    double F_C = 0, F_R = 1;
    double nabla, nabla_radiative; nabla = nabla_radiative = nabla_ad();
    double eps_PPI = 0;

    double drdm, dPdm, dLdm, dTdm;
    double mu_0 = StateEquations::mu_0(MF);

    Opacity kappa;

    double p_max = 0.005; // max fractional change in any variable
    double dms [5];

    int count = 0;

    bool dss = false;
    if (dm == 0) {
        dss = true;
        dm = -1e10;
    }

    while (m > 0 and r > 0 and L > 0 and T > 0 and rho > 0) {
        if (count++ % 10 == 0) {
            ss << m << ' ' << r << ' ' << P << ' '
               << L << ' ' << T << ' ' << rho
               << ' ' << eps;
           ss << ' ' << F_C << ' ' << eps_PPI;
           ss << ' ' << nabla << ' ' << nabla_radiative << '\n';

        }
        if (count % 100 == 0) {
            double percent = 100 - (m / M_0) * 100;
            std::cout << "\rProgress: " << percent << "%  ";
            std::cout << std::flush;
        }


        drdm = RHS_r(r, rho);
        dPdm = RHS_P(m, r);
        dLdm = eps = energy(T, rho, MF, energy_terms);
        dTdm = RHS_T(T, rho, L, r, kappa);

        eps_PPI = energy_terms(_p, _p) + energy_terms(_3He, _3He);


        calculate_convection(T, P, r, L, rho, m, mu_0, nabla_radiative, nabla,
                             dTdm, F_C, F_R, kappa);

        if (dss) {
            dms[0] = abs(p_max*r / drdm);
            dms[1] = abs(p_max*P / dPdm);
            dms[2] = abs(p_max*L / dLdm);
            dms[3] = abs(p_max*T / dTdm);
            dms[4] = abs(p_max*m);
            dm = - (*min_element(dms, dms+5));
        }

        r += drdm * dm;
        P += dPdm * dm;
        L += dLdm * dm;
        T += dTdm * dm;
        rho = StateEquations::rho(T, P, mu_0);
        m += dm;

        if (m < 0 or r < 0 or L < 0 or T < 0 or rho < 0 or dm > -1) {
            std::cout << "Unphysical at count = " << count << '\n'
            << "dm = " << dm << '\n'
            << "m/M_0 = " << m/M_0 << '\n'
            << "r/R_0 = " << r/R_0 << '\n'
            << "L/L_0 = " << L/L_0 << '\n'
            << "T = " << T << '\n'
            << "rho = " << rho << '\n';
            break;
        }
    }

    std::cout << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << ' ' << dm;
    std::cout << ' ' << F_C << ' ' << eps_PPI;
    std::cout << ' ' << nabla << ' ' << nabla_radiative << '\n';

    ss << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << ' ' << eps;
    ss << ' ' << F_C << ' ' << eps_PPI;
    ss << ' ' << nabla << ' ' << nabla_radiative;
    return ss.str();
}



std::string Integrate::integrate(double L_0, double T_0, double P_0, double rho_0, double M_0, double R_0, MassFractions MF, double dm) {
  std::stringstream ss;
  ss << "# m \t r \t P \t L \t T \t rho \t epsilon \n";

  arma::mat energy_terms (N_PARTICLES, N_PARTICLES);

  double r = R_0, T = T_0, L = L_0, P = P_0, rho = rho_0, m = M_0, eps;;
  double drdm, dPdm, dLdm, dTdm;
  double mu_0 = StateEquations::mu_0(MF);

  Opacity kappa;

  double p_max = 0.005; // max fractional change in any variable
  double dms [5];

  int count = 0;

  bool dss = false;
  if (dm == 0) {
    dss = true;
    dm = -1e10;
  }

  while (m > 0 and r > 0 and L > 0 and T > 0 and rho > 0) {
    if (count++ % 10 == 0) {
      ss << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << ' ' << eps << '\n';
    }
    if (count % 100 == 0) {
      double percent = 100 - (m / M_0) * 100;
      std::cout << "\rProgress: " << percent << "%  ";
      std::cout << std::flush;
    }


    drdm = RHS_r(r, rho);
    dPdm = RHS_P(m, r);
    dLdm = eps = energy(T, rho, MF, energy_terms);
    dTdm = RHS_T(T, rho, L, r, kappa);

    if (dss) {
      dms[0] = abs(p_max*r / drdm);
      dms[1] = abs(p_max*P / dPdm);
      dms[2] = abs(p_max*L / dLdm);
      dms[3] = abs(p_max*T / dTdm);
      dms[4] = abs(p_max*m);
      dm = - (*min_element(dms, dms+5));
    }

    r += drdm * dm;
    P += dPdm * dm;
    L += dLdm * dm;
    T += dTdm * dm;
    rho = StateEquations::rho(T, P, mu_0);
    m += dm;

    if (m < 0 or r < 0 or L < 0 or T < 0 or rho < 0 or dm > -1) {
      std::cout << "Unphysical at count = " << count << '\n'
		<< "dm = " << dm << '\n'
		<< "m/M_0 = " << m/M_0 << '\n'
		<< "r/R_0 = " << r/R_0 << '\n'
		<< "L/L_0 = " << L/L_0 << '\n'
      		<< "T = " << T << '\n'
		<< "rho = " << rho << '\n';
      break;
    }
  }

  std::cout << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << ' ' << dm << '\n';
  ss << m << ' ' <<  r << ' ' << P << ' ' << L << ' ' << T << ' ' << rho << ' ' << eps;
  return ss.str();
}
