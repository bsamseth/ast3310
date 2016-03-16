#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <armadillo>

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

double opacity(double T, double rho) {
  vec log10T = read_log10T();
  vec log10R = read_log10R();
  mat kappa = read_opacity(log10T.size(), log10R.size());

  double log10R_wanted = log10(rho / pow((T*1e-6),3));
  double log10T_wanted = log10(T);
  
  int T_index = find_closest_index(log10T_wanted, log10T);
  int R_index = find_closest_index(log10R_wanted, log10R);


  // double x1 = log10R(R_index+1) , x2 = log10R(R_index), x = log10R_wanted;
  // double y1 = log10T(T_index+1) , y2 = log10T(T_index), y = log10T_wanted;
  // double kappa_11 = kappa(T_index+1, R_index),   kappa_12 = kappa(T_index, R_index);
  // double kappa_21 = kappa(T_index+1, R_index+1), kappa_22 = kappa(T_index, R_index+1);

  
  // double kappa_result = 1./((x2-x1)*(y2-y1)) * (kappa_11*(x2-x)*(y2-y)
  // 						+ kappa_21*(x-x1)*(y2-y)
  // 						+ kappa_12*(x2-x)*(y-y1)
  // 						+ kappa_22*(x-x1)*(y-y1));

  // cout << "kappa_base = " << kappa(T_index, R_index) << "\n";


  // ONLY TEMPORARY, USING NEAREST NEIGBHOUR INTERPOLATION
  double kappa_result = kappa(T_index, R_index);
  
  // cout << std::setprecision(3) << std::fixed
  //      << "log10T = " << log10T_wanted << ", log10R = " << log10R_wanted << " -> kappa = " << kappa_result << "\n";
  
  return kappa_result;
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
