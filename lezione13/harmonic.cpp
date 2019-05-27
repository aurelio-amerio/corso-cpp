/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 13

  harmonic oscillator
*/

#include "../lib/ode.h"
#include <fstream>
#include <iostream>
#include <math.h>

#define PRINT 1

using namespace std;

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

// void velocity_Verlet_print(double *X, double *V,
//                            void (*acc)(double *X, double *res, int n_part),
//                            double h, int n_part, int n_steps) {
//   double vn12[n_part];
//   double accel[n_part];
//   ofstream file;
//   file.open("harmonic_verlet.dat");
//   file << "0 " << X[0] << " " << V[0] << endl;
//
//   acc(X, accel, n_part); // initialize acceleration
//
//   for (int j = 1; j <= n_steps; j++) {
//     // compute X(n+1)
//     for (int i = 0; i < n_part; i++) {
//       vn12[i] = V[i] + h / 2 * accel[i];
//       X[i] = X[i] + h * vn12[i];
//     }
//     acc(X, accel, n_part); // update acceleration -> a(x n+1)
//
//     // compute v(n+1)
//     for (int i = 0; i < n_part; i++) {
//       V[i] = vn12[i] + h / 2 * accel[i];
//     }
//     file << j << " " << X[0] << " " << V[0] << endl;
//   }
//
//   return;
// }

void acc(double *X, double *res, int n_part) {
  double omega = 1;
  for (int i = 0; i < n_part; i++) {
    res[i] = -omega * omega * X[i];
  }
  return;
}

void rhs_1(double t, double *Y, double *R) {
  double x, vx;

  x = Y[0];
  vx = Y[1];

  R[0] = vx;
  R[1] = -x;

  return;
}

int main() {

  // velocity Verlet
  double X[] = {1};
  double V[] = {0};
  double pi = 3.1415926;
  double periodo = 2 * pi;
  double h = 0.02 * periodo;
  int n_steps = 50 * 10;

  velocity_Verlet(X, V, acc, h, 1, n_steps);
  cout << "verlet:\n";
  cout << X[0] << " " << V[0] << endl;

  // Verlet 4
  X[0] = 1;
  V[0] = 0;
  verlet4(X, V, acc, h, 1, n_steps);
  cout << "verlet 4:\n";
  cout << X[0] << " " << V[0] << endl;

  // Runge-Kutta 2
  ofstream file1;
  file1.open("harmonic_rk.dat");
  double Y[] = {1, 0};
  double t = 0;
  for (int i = 0; i < n_steps; i++) {
    RKStep(t, Y, rhs_1, h, 2);
    t += h;
    file1 << i << " " << Y[0] << " " << Y[1] << endl;
  }
  cout << "rk: \n";
  cout << Y[0] << " " << Y[1] << endl;
  file1.close();

  // Runge-Kutta 4
  ofstream file2;
  file2.open("harmonic_rk4.dat");
  Y[0] = 1;
  Y[1] = 0;
  t = 0;
  for (int i = 0; i < n_steps; i++) {
    RK4Step(t, Y, rhs_1, h, 2);
    t += h;
    file2 << i << " " << Y[0] << " " << Y[1] << endl;
  }
  cout << "rk4: \n";
  cout << Y[0] << " " << Y[1] << endl;
  file2.close();

  return 0;
}
