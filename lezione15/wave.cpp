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
#define STEP 3

double g_k = 0;

void rhs(double r, double *Y, double *R) {
  double phi, s, k;
  k = g_k;
  phi = Y[0];
  s = Y[1];
  // cout << "K: " << k << endl;

  R[0] = s;
  R[1] = -k * k * phi;

  return;
}

double residual(double k) {
  double Y[] = {0, 1};
  g_k = k;
  double r = 0.;
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
  g_k = 4;
  file1.open("wave4.dat");
  double Y[] = {0, 1};
  double r = 0;
  int n_steps = 100;
  double rmax = 1.;
  double dr = rmax / n_steps;

  for (int i = 0; i < n_steps; i++) {
    RK4Step(r, Y, rhs, dr, 2);
    r += dr;
    file1 << double(i) * dr << " " << Y[0] << " " << Y[1] << endl;
  }
  file1.close();
#endif

#if STEP == 1
  cout << residual(3.14) << endl;
#endif

#if STEP == 2
  double res = bisec(residual, 1, 5, 1e-9, 1e-9);
  cout << "bisec: " << res << endl;

  res = secant(residual, 1, 5, 1e-9, 1e-9);
  cout << "secant: " << res << endl;

#endif
#if STEP == 3
  int n_roots = 0;
  int n_int = 20;
  double xL[n_int];
  double xR[n_int];

  bracket(residual, 1, 20, n_int, xL, xR, n_roots);
  double res;
  cout << "nroots: " << n_roots << endl;
  cout << "secant: " << endl;
  for (int i = 0; i < n_roots; i++) {
    res = secant(residual, xL[i], xR[i], 1e-9, 1e-9);
    cout << "k= " << res << endl;
  }

#endif

  return 0;
}
