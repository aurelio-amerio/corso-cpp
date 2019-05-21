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

void rhs(double x, double *Y, double *R) {
  double xdot, ydot;
  xdot = Y[0];
  ydot = Y[1];
  R[0] = ydot;
  R[1] = -xdot;
  return;
}

void RKStep(double t, double *Y, void (*Ydot)(double, double *, double *),
            double dt, int neq) {
  // Runge-Kutta step using Midpoint integration

  double Y1[neq]; // il vettore che contiene le soluzioni approssimate
  double k1[neq]; // rhs 1
  double k2[neq]; // rhs 2

  Ydot(t, Y, k1); // calcola il primo rhs per determinare Y1 approx
  for (int n = 0; n < neq; n++) {
    Y1[n] = Y[n] + 0.5 * dt * k1[n];
  }

  Ydot(t + 0.5 * dt, Y1,
       k2); // calcola il secondo rhs per determinare Y raffinato
  for (int n = 0; n < neq; n++) {
    Y[n] += dt * k2[n];
  }

  return;
}

void EulerStep(double t, double *Y, void (*Ydot)(double, double *, double *),
               double dt, int neq) {
  double rhs[neq]; // il vettore che contiene gli elementi rhs
  Ydot(t, Y,
       rhs); // la funzione che calcole gli elemnti di destra del sist di eq
  for (int n = 0; n < neq; n++) {
    Y[n] += dt * rhs[n];
  }
  return;
}

// double exact(double x) { return exp(-x * x / 2); }

int main() {
  fstream file;
  file.open("rk_ode.dat");
  // file2.open("euler_ode.dat");
  double tMAX = 20. * 3.1415926;
  int n_steps = 200;
  double dt = tMAX / n_steps;
  int neq = 2;

  double Y[] = {1, 0};
  double t = 0;
  file << t << " " << Y[0] << " " << Y[1] << endl;

  for (int n = 0; n < n_steps; n++) {
    RKStep(t, Y, rhs, dt, neq);
    t += dt;

    file << t << " " << Y[0] << " " << Y[1] << endl;
  }
  cout << "x(20π): " << Y[0] << "\ty(20π): " << Y[1] << endl;

  file.close();
  // file2.close();
  return 0;
}
