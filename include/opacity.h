#ifndef OPACITY_H
#define OPACITY_H

#include <armadillo>

const std::string opacities_filename = "opacity.txt";

/**
 * Class used to calculate opacity values through interpolating a data file.
 *
 * When an object of this class is instantiated, the data file is loaded and stored
 * in a matrix. The object can then be used as a function, preforming a bilinear
 * interpolation of the data matrix in order to provide the estimated value.
 * Using an object enables the user to only load the data once, causing a
 * significant increase in speed, compared to the alliterative.
 */
class Opacity {
 public:
  
  /**
   * Instantiates an object using the default data file.
   */
  Opacity();

  /**
   * Return the estimated opacity value.
   * Use bilinear interpolation to find the value best suited to the inputs.
   * Extrapolating is currently not available, and behaviour is undefined for this case.
   *
   * @param T Temperature [K]
   * @param rho Density [kg m^-3]
   * @return opacity value, kappa(T, rho)
   */
  double operator() (double T, double rho);

 private:
  /*
   * The remaining methods are helpers used in the public methods.
   */
  
  int find_closest_index(double a, arma::vec A);
  double interp2d(double q11, double q12, double q21, double q22, double x1, double x2, double y1, double y2, double x, double y);
  arma::vec read_log10R();
  arma::vec read_log10T();
  arma::mat read_opacity(int T_size, int R_size);

  arma::vec log10T;
  arma::vec log10R;
  arma::mat kappa;
};

#endif
