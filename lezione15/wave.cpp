/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 15

  wave
*/

// #include "../lib/ode.h"
#include "ode.h"
#include "root_finders.h"
#include <fstream>
#include <iostream>
using namespace std;

#define PI 3.1415926
#define STEP 0

void rhs(double r, double *Y, double *R) {
  double phi, s, k;

  phi = Y[0];
  s = Y[1];
  k = Y[2];

  R[0] = s;
  R[1] = -k * k * phi;

  return;
}

double residual(double k) {

  double Y[] = {0, 1, k};
  double r = 0;
  int n_steps = 100;
  double rmax = 1.;
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

  double residual = Y[0];
  return residual;
}

int main() {
#if STEP == 0
  // Runge-Kutta 4 s0
  ofstream file1;
  double s = 1.;
  double k = 1;
  file1.open("wave1.dat");
  double Y[] = {0, 1, k};
  double r = 0;
  int n_steps = 100;
  double rmax = 1.;
  double dr = rmax / n_steps;

  for (int i = 0; i < n_steps; i++) {
    RK4Step(r, Y, rhs, dr, 2);
    r += dr;
    file1 << double(i)/dr << " " << Y[0] << " " << Y[1] << endl;
  }
  file1.close();
#endif

#if STEP == 1
  cout << residual(PI) << endl;
#endif

#if STEP == 2
  double res = bisec(residual, 1, 5, 1e-9, 1e-9);
  cout << "bisec: " << res << endl;

  res = secant(residual, 1, 5, 1e-9, 1e-9);
  cout << "secant: " << res << endl;

#endif
#if STEP == 3
  int n_roots = 1;
  double xL[2];
  double xR[2];
  int n_int = 10;
  bracket(residual, 0, 5, n_int, xL, xR, n_roots);

  double res = secant(residual, xL[0], xR[0], 1e-9, 1e-9);
  cout << "secant: " << res << endl;

  double k = res;
  double Y[] = {0, 1, k};
  double r = 0;
  int n_steps = 100;
  double rmax = 1.;
  double dr = rmax / n_steps;

  for (int i = 0; i < n_steps; i++) {
    RK4Step(r, Y, rhs, dr, 2);
    r += dr;
  }

  cout << "res: " << Y[0] << endl;
  cout << "true res: " << PI << endl;

#endif

  return 0;
}
