/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 11

  runge-kutta method
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

void dYdx(double x, double *Y, double *R) {
  double y;
  y = Y[0];
  R[0] = -x * y;
  return;
}

void RKStep(double x, double *Y, void (*Ydot)(double, double *, double *),
            double dx, int neq) {
  // Runge-Kutta step using Midpoint integration

  double Y1[neq]; // il vettore che contiene le soluzioni approssimate
  double k1[neq]; // rhs 1
  double k2[neq]; // rhs 2

  Ydot(x, Y, k1); // calcola il primo rhs per determinare Y1 approx
  for(int n=0; n<neq; n++)
  {
    Y1[n]=Y[n]+0.5*dx*k1[n];
  }

  Ydot(x+0.5*dx, Y1, k2); // calcola il secondo rhs per determinare Y raffinato
  for(int n=0; n<neq; n++)
  {
    Y[n]+=dx*k2[n];
  }

  return;
}

double exact(double x) { return exp(-x * x / 2); }

int main() {
  double xMAX = 3;
  double dx = 0.25;
  int neq = 1;
  int n_steps = int(ceil(xMAX / dx));
  double Y[] = {1};
  double x = 0;
  double abs_err = 0.;
  double relative_err = 0.;
  cout << "x: " << x << "\tY(t): " << Y[0] << "\t abs err: " << abs_err
       << "\t rel err " << relative_err << endl;

  for (int n = 0; n < n_steps; n++) {
    RKStep(x, Y, dYdx, dx, neq);
    x += dx;
    abs_err = fabs(Y[0] - exact(x));
    relative_err = fabs((Y[0] - exact(x)) / exact(x));
    cout << "x: " << x << "\tY(t): " << Y[0] << "\t abs err: " << abs_err
         << "\t rel err " << relative_err << endl;
  }
  cout << "RK solution: " << Y[0] << endl;
  // cout << "exact: " << exact(x)<<endl;
  // euler_print(dydx, exact, x, y0, 0.5, "ode05.dat");
  // euler_print(dydx, exact, x, y0, 0.25, "ode025.dat");
  // euler_print(dydx, exact, x, y0, 0.1, "ode01.dat");
  // euler_print(dydx, exact, x, y0, 0.01, "ode001.dat");
  return 0;
}
