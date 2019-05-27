// a library with helpful functions to solve ODEs

// #include "../lib/ode.h"
#include <fstream>
#include <math.h>

#define PRINT 0

using namespace std;

// prototype

void RKStep(double t, double *Y, void (*Ydot)(double, double *, double *),
            double dt, int neq);
void RK4Step(double t, double *Y, void (*Ydot)(double, double *, double *),
             double dt, int neq);
void EulerStep(double t, double *Y, void (*Ydot)(double, double *, double *),
               double dt, int neq);

void velocity_Verlet(double *X, double *V,
                     void (*acc)(double *X, double *res, int n_part), double h,
                     int n_part, int n_steps);

void verlet4(double *X, double *V,
             void (*acc)(double *X, double *res, int n_part), double h,
             int n_part, int n_steps);

// implementation
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

void velocity_Verlet(double *X, double *V,
                     void (*acc)(double *X, double *res, int n_part), double h,
                     int n_part, int n_steps) {
  double vn12[n_part];
  double accel[n_part];
#if PRINT
  ofstream file;
  file.open("harmonic_verlet.dat");
  file << "0 " << X[0] << " " << V[0] << endl;
#endif
  acc(X, accel, n_part); // initialize acceleration

  for (int j = 0; j < n_steps; j++) {
    // compute X(n+1)
    for (int i = 0; i < n_part; i++) {
      vn12[i] = V[i] + h * 0.5 * accel[i];
      X[i] = X[i] + h * vn12[i];
    }
    acc(X, accel, n_part); // update acceleration -> a(x n+1)

    // compute v(n+1)
    for (int i = 0; i < n_part; i++) {
      V[i] = vn12[i] + h * 0.5 * accel[i];
    }
#if PRINT
    file << j << " " << X[0] << " " << V[0] << endl;
#endif
  }
#if PRINT
  file.close();
#endif
  return;
}

void verlet4(double *X, double *V,
             void (*acc)(double *X, double *res, int n_part), double h,
             int n_part, int n_steps) {
  static const double gamma = 1. / (2. - pow(2., 1. / 3.));
  double accel[n_part];
  acc(X, accel, n_part); // initialize acceleration

#if PRINT
  ofstream file;
  file.open("harmonic_verlet4.dat");
  file << "0 " << X[0] << " " << V[0] << endl;
#endif

  for (int j = 0; j < n_steps; j++) {
    // first step
    for (int i = 0; i < n_part; i++) {
      V[i] = V[i] + gamma * h * 0.5 * accel[i];
      X[i] = X[i] + gamma * h * V[i];
    }
    acc(X, accel, n_part); // update acceleration

    // second step
    for (int i = 0; i < n_part; i++) {
      V[i] = V[i] + (1 - gamma) * h * 0.5 * accel[i];
      X[i] = X[i] + (1 - 2 * gamma) * h * V[i];
    }
    acc(X, accel, n_part); // update acceleration

    // third step
    for (int i = 0; i < n_part; i++) {
      V[i] = V[i] + (1 - gamma) * h * 0.5 * accel[i];
      X[i] = X[i] + gamma * h * V[i];
    }
    acc(X, accel, n_part); // update acceleration

    // finally compute v
    for (int i = 0; i < n_part; i++) {
      V[i] = V[i] + gamma * h * 0.5 * accel[i];
    }
#if PRINT
    file << j << " " << X[0] << " " << V[0] << endl;
#endif
  }
#if PRINT
  file.close();
#endif
  return;
}
