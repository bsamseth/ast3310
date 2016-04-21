#include <cmath>
#include <iostream>

#include "thirdordersolver.hpp"

using std::abs;


int solve3order(double* x, double a, double b, double c, double d) {
    const double eps = 1e-14;
    double TwoPi = 2*M_PI;

    // algorith based on coeff
    // x^3 + ax^2 + bx + c
    b /= a; c /= a; d /= a;
    a = b;
    b = c;
    c = d;

	double a2 = a*a;
    double q  = (a2 - 3*b)/9;
	double r  = (a * (2 * a2 - 9 * b) + 27 * c) / 54;
    double r2 = r*r;
	double q3 = q*q*q;
	double A, B;

    if(r2 < q3) {
        double t = r / sqrt(q3);
		if( t < -1) t = -1;
		if( t> 1) t = 1;
        t = acos(t);
        a /= 3; q = -2 * sqrt(q);
        x[0] = q * cos(t / 3) - a;
        x[1] = q * cos((t + TwoPi) / 3) - a;
        x[2] = q * cos((t - TwoPi) / 3) - a;
        return 3;
    }
    else {
        A = -pow(fabs(r) + sqrt(r2 - q3), 1./3);
		if( r < 0 ) A = -A;
		B = A == 0 ? 0 : q/A;

		a /= 3;
		x[0] = (A + B) - a;
        x[1] = -0.5 * (A + B) - a;
        x[2] = 0.5 * sqrt(3) * (A - B);
		if (fabs(x[2]) < eps) {
            x[2] = x[1];
            return 2;
        }
        return 1;
    }
}
