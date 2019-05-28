/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 15

  poisson
*/

// #include "../lib/ode.h"
#include "ode.h"
#include <fstream>
#include <iostream>
using namespace std;

#define PI 3.1415926
#define S 1.

void rhs(double r, double *Y, double *R) {
  double phi, s;
  double rho;

  s = S;

  phi = Y[0];
  s = Y[1];

  rho = 1. / (8 * PI) * exp(-r);

  R[0] = s;
  R[1] = -4 * PI * r * rho;

  return;
}

int main() {

  // Runge-Kutta 4 s0
  ofstream file1;
  double s = S;
  file1.open("poisson_s1.dat");
  double Y[] = {0, s};
  double r = 0;
  double dr = 20. / 1000.;
  int n_steps = 1000;
  for (int i = 0; i < n_steps; i++) {
    RK4Step(r, Y, rhs, dr, 2);
    r += dr;
    file1 << i << " " << Y[0] << " " << Y[1] << endl;
  }
  file1.close();

  return 0;
}
