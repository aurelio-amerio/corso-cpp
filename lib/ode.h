#include <math.h>
using namespace std;

//prototype

void RKStep(double t, double *Y, void (*Ydot)(double, double *, double *),
            double dt, int neq);
void RK4Step(double t, double *Y, void (*Ydot)(double, double *, double *),
             double dt, int neq);
void EulerStep(double t, double *Y, void (*Ydot)(double, double *, double *),
               double dt, int neq);

//implementation
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

void RK4Step(double t, double *Y, void (*Ydot)(double, double *, double *),
             double dt, int neq) {
  // Runge-Kutta step using Midpoint integration

  double Y1[neq], Y2[neq], Y3[neq];
  double k1[neq];
  double k2[neq];
  double k3[neq];
  double k4[neq];

  Ydot(t, Y, k1); // set k1

  // compute Y1 for k2
  for (int n = 0; n < neq; n++) {
    Y1[n] = Y[n] + 0.5 * dt * k1[n];
  }

  Ydot(t + 0.5 * dt, Y1, k2); // set k2

  // compute Y2 for k3
  for (int n = 0; n < neq; n++) {
    Y2[n] = Y[n] + 0.5 * dt * k2[n];
  }

  // compute Y3 for k4
  Ydot(t + 0.5 * dt, Y2, k3); // set k3
  for (int n = 0; n < neq; n++) {
    Y3[n] = Y[n] + dt * k3[n];
  }

  Ydot(t + dt, Y3, k4); // set k4

  // sum intermediate computations
  for (int n = 0; n < neq; n++) {
    Y[n] += dt / 6. * (k1[n] + 2 * k2[n] + 2 * k3[n] + k4[n]);
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
