#ifndef OPACITY_H
#define OPACITY_H

#include <armadillo>

const std::string opacities_filename = "opacity.txt";


class Opacity {
 public:
  Opacity();
  double operator() (double T, double rho);
  int find_closest_index(double a, arma::vec A);
  double interp2d(double q11, double q12, double q21, double q22, double x1, double x2, double y1, double y2, double x, double y);
  arma::vec read_log10R();
  arma::vec read_log10T();
  arma::mat read_opacity(int T_size, int R_size);

  arma::vec log10T;
  arma::vec log10R;
  arma::mat kappa;
};

double opacity(double T, double rho);

#endif
