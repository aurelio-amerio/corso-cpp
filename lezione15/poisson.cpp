/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 15

  poisson
*/

// #include "../lib/ode.h"
#include "ode.h"
#include "root_finders.h"
#include <fstream>
#include <iostream>
using namespace std;

#define PI 3.1415926
#define STEP 3

void rhs(double r, double *Y, double *R) {
  double phi, s;
  double rho;

  phi = Y[0];
  s = Y[1];

  rho = 1. / (8 * PI) * exp(-r);

  R[0] = s;
  R[1] = -4 * PI * r * rho;

  return;
}

double residual(double s) {

  double Y[] = {0, s};
  double r = 0;
  int n_steps = 1000;
  double rmax = 20.;
  double dr = rmax / n_steps;

  for (int i = 0; i < n_steps; i++) {
    RK4Step(r, Y, rhs, dr, 2);
    // if (i == (n_steps - 2)) {
    //   r = rmax;
    // } else {
    //   r += dr;
    // }
    r += dr;
  }

  double residual = Y[0] - 1.;
  return residual;
}

int main() {
#if STEP == 0
  // Runge-Kutta 4 s0
  ofstream file1;
  double s = 1.;
  file1.open("poisson_s1.dat");
  double Y[] = {0, s};
  double r = 0;
  double rmax = 20.;
  int n_steps = 1000;
  double dr = rmax / n_steps;

  for (int i = 0; i < n_steps; i++) {
    RK4Step(r, Y, rhs, dr, 2);
    r += dr;
    file1 << i << " " << Y[0] << " " << Y[1] << endl;
  }
  file1.close();
#endif

#if STEP == 1
  cout << residual(0.4) << endl;
#endif

#if STEP == 2
  double res = bisec(residual, 0.3, 0.6, 1e-9, 1e-9);
  cout << "bisec: " << res << endl;

  res = secant(residual, 0.3, 0.6, 1e-9, 1e-9);
  cout << "secant: " << res << endl;



#endif
#if STEP == 3
  int n_roots = 1;
  int n_int = 10;
  double xL[n_int];
  double xR[n_int];

  bracket(residual, 0, 1, n_int, xL, xR, n_roots);

  double res = secant(residual, xL[0], xR[0], 1e-9, 1e-9);
  cout << "secant: " << res << endl;

  double s = res;
  double Y[] = {0, s};
  double r = 0;
  double rmax = 20.;
  int n_steps = 1000;
  double dr = rmax / n_steps;

  for (int i = 0; i < n_steps; i++) {
    RK4Step(r, Y, rhs, dr, 2);
    r += dr;
  }

  cout << "res: " << Y[0] << endl;
  cout << "true res: " << 1. - 0.5 * (20 + 2) * exp(-20) << endl;

#endif

  return 0;
}
