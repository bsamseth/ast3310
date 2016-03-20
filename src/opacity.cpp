#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <armadillo>

#include "constants.h"
#include "opacity.h"

using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::istringstream;
using std::ifstream;
using std::vector;
using std::abs;
using namespace arma;

mat read_opacity(int T_size, int R_size);
vec read_log10T();
vec read_log10R();
int find_closest_index(double a, vec A);
double interp2d(double q11, double q12, double q21, double q22, double x1, double x2, double y1, double y2, double x, double y) ;

double opacity(double T, double rho) {
  vec log10T = read_log10T();
  vec log10R = read_log10R();
  mat kappa = read_opacity(log10T.size(), log10R.size());

  double rho_cgs = rho / 1e3;
  double T6 = T * 1e-6;
  double R = rho_cgs / (T6*T6*T6);
  double log10R_wanted = log10(R);
  double log10T_wanted = log10(T);

  int i_T = find_closest_index(log10T_wanted, log10T);
  int i_R = find_closest_index(log10R_wanted, log10R);

  double q11 = kappa( i_T, i_R);
  double q12 = kappa(i_T, i_R+1);
  double q21 = kappa(i_T+1, i_R);
  double q22 = kappa(i_T+1, i_R+1);
  double x1 = log10T(i_T);
  double x2 = log10T(i_T+1);
  double y1 = log10R(i_R);
  double y2 = log10R(i_R+1);
  double x = log10T_wanted;
  double y = log10R_wanted;

  double kappa_result = interp2d(q11,q12,q21,q22,x1,x2,y1,y2,x,y);

  if (i_T == log10T.size()-1) {
    cout << "Possible extrapolating in kappa reader (T)" << '\n';
    cout << "Input was: T = " << T << ", rho = " << rho << '\n';
    cout << "In log10: logT = " << log10T_wanted << ", logR = " << log10R_wanted << '\n';
    exit(1);
  }
  if (i_R == log10R.size()-1) {
    cout << "Possible extrapolating in kappa reader (R)" << '\n';
    cout << "Input was: T = " << T << ", rho = " << rho << '\n';
    cout << "In log10: logT = " << log10T_wanted << ", logR = " << log10R_wanted << '\n';
    exit(1);
  }
  

  double kappa_SI = pow(10, kappa_result) / 10;
  return kappa_SI;
}


int find_closest_index(double a, vec A) {
  int index = 0;
  double diff = a - A(0), new_diff;

  for (int i = 1; i < A.size(); i++) {
    new_diff = a - A(i);
    if (new_diff < diff and new_diff >= 0) {
      diff = new_diff;
      index = i;
    }
  }
  return index;
}


double interp2d(double q11, double q12, double q21, double q22, double x1, double x2, double y1, double y2, double x, double y) 
{
    double x2x1, y2y1, x2x, y2y, yy1, xx1;
    x2x1 = x2 - x1;
    y2y1 = y2 - y1;
    x2x = x2 - x;
    y2y = y2 - y;
    yy1 = y - y1;
    xx1 = x - x1;
    return 1.0 / (x2x1 * y2y1) * (
        q11 * x2x * y2y +
        q21 * xx1 * y2y +
        q12 * x2x * yy1 +
        q22 * xx1 * yy1
    );
}


vec read_log10R() {
  ifstream infile (opacities_filename);
  string line, tmp;
  // read first line
  getline(infile, line);
  infile.close();
  istringstream iss (line);
  iss >> tmp; // read header "logT"

  // read R values
  vector<double> log10R = {};
  double number;
  while (iss >> number) {
    log10R.push_back(number);
  }
  return vec(log10R);
}

vec read_log10T() {
  ifstream infile (opacities_filename);
  string line, tmp;
  double number;

  // read first line
  getline(infile, line);
  // file has empty line 2
  getline(infile, line);

  istringstream iss;
  // read T values
  vector<double> log10T = {};
  while (getline(infile, line)) {
    iss = istringstream(line);
    iss >> number;
    log10T.push_back(number);
  }
  infile.close();
  return vec(log10T);
}

mat read_opacity(int T_size, int R_size) {
  ifstream infile (opacities_filename);
  istringstream iss;
  string line;
  double number;
  getline(infile, line); // empty lines
  getline(infile, line);

  mat kappa (T_size, R_size);
  int i = 0;
  while (getline(infile, line)) {
    iss = istringstream(line);
    iss >> number; // skip log10T value
    int j = 0;
    while (iss >> number) {
      kappa(i,j++) = number;
    }
    i++;
  }
  infile.close();
  return kappa;
}
