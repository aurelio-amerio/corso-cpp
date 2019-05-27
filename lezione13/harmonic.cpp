/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 13

  harmonic oscillator
*/

#include <fstream>
#include <iostream>
#include <math.h>
#include "../lib/ode.h"
using namespace std;

void velocity_Verlet(double *X, double *V,
                     void (*acc)(double *X, double *res, int n_part), double h,
                     int n_part, int n_steps) {
  double vn12[n_part];
  double accel[n_part];
  acc(X, accel, n_part); // initialize acceleration

  for (int j = 0; j < n_steps; j++) {
    // compute X(n+1)
    for (int i = 0; i < n_part; i++) {
      vn12[i] = V[i] + h / 2 * accel[i];
      X[i] = X[i] + h * vn12[i];
    }
    acc(X, accel, n_part); // update acceleration -> a(x n+1)

    // compute v(n+1)
    for (int i = 0; i < n_part; i++) {
      V[i] = vn12[i] + h / 2 * accel[i];
    }
  }

  return;
}

void velocity_Verlet_print(double *X, double *V,
                     void (*acc)(double *X, double *res, int n_part), double h,
                     int n_part, int n_steps) {
  double vn12[n_part];
  double accel[n_part];
  ofstream file;
  file.open("harmonic_verlet.dat");
  file<<"0 "<<X[0]<<" "<<V[0]<<endl;

  acc(X, accel, n_part); // initialize acceleration

  for (int j = 1; j <= n_steps; j++) {
    // compute X(n+1)
    for (int i = 0; i < n_part; i++) {
      vn12[i] = V[i] + h / 2 * accel[i];
      X[i] = X[i] + h * vn12[i];
    }
    acc(X, accel, n_part); // update acceleration -> a(x n+1)

    // compute v(n+1)
    for (int i = 0; i < n_part; i++) {
      V[i] = vn12[i] + h / 2 * accel[i];
    }
    file<<j<<" "<<X[0]<<" "<<V[0]<<endl;
  }

  return;
}

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

  //velocity Verlet
  double X[] = {1};
  double V[] = {0};
  double pi = 3.1415926;
  double periodo = 2 * pi;
  double h = 0.02 * periodo;
  int n_steps = 50 * 10;

  velocity_Verlet_print(X, V, acc, h, 1, n_steps);
  cout<<"verlet:\n";
  cout << X[0] << " " << V[0] << endl;

  //Runge-Kutta 2
  ofstream file1;
  file1.open("harmonic_rk.dat");
  double Y[]={1,0};
  double t=0;
  for(int i=0; i<n_steps; i++)
  {
    RKStep(t, Y, rhs_1, h, 2);
    t += h;
    file1<<i<<" "<<Y[0]<<" "<<Y[1]<<endl;
  }
  cout<<"rk: \n";
  cout << Y[0] << " " << Y[1] << endl;
  return 0;
}
