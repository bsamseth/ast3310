#ifndef THIRD_ORDER_SOLVER
#define THIRD_ORDER_SOLVER

/**
* Solve cubic equation ax^3 + bx^2 + cx + d = 0.
*
* The array `x` will contain the solutions after call to the function.
* Three cases:
*   3 real roots: => x[0], x[1], x[2],    return 3
*   2 real roots: x[0], x[1],             return 2
*   1 real root : x[0], x[1] +- i * x[2], return 1
*
* Modified (a little) from code found
* [here](http://math.ivanovo.ac.ru/dalgebra/Khashin/poly/index.html).
*
* @param  x array of size 3
* @param  a coefficient of x^3
* @param  b coefficient of x^2
* @param  c coefficient of x^1
* @param  d coefficient of x^0
* @return number of real roots in solution array `x`
*/
int solve3order(double* x, double a, double b, double c, double d);

#endif
