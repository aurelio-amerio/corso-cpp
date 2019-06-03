/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 16

  quantum harmonic oscillator
*/

#include "ode.h"
#include "root_finders.h"
#include <fstream>
#include <iostream>
using namespace std;

#define PI 3.1415926
#define STEP 1

double g_E = 0.5;

void rhs(double x, double *Y, double *R) {
  double phi, s;
  double V;

  phi = Y[0];
  s = Y[1];

  V = 0.5 * x * x;

  R[0] = s;
  R[1] = -2 * g_E * phi + 2 * V * phi;

  return;
}

double asymp(double x) { return sqrt(PI) * exp(-x * x * 0.5) / sqrt(fabs(x)); }

double dasymp(double x) {
  static const double sqrt_pi = sqrt(PI);
  return -exp(-x * x * 0.5) * sqrt_pi / (2 * pow(x, 1.5)) -
         exp(x * x * 0.5) * sqrt_pi * sqrt(fabs(x));
}

double residual(double En) {
  g_E = En;

  double xmin = -10;
  double xmax = 10;

  // double y0 = asymp(xmin);
  // double v0 = dasymp(xmin);
  // double yfin = asymp(xmax);
  // double vfin = dasymp(xmax);
  double y0 = exp(-xmin*xmin*0.5);
  double v0 = -xmin*exp(-xmin*xmin*0.5);
  double yfin = exp(-xmax*xmax*0.5);
  double vfin = -xmax*exp(-xmax*xmax*0.5);

  double Y1[] = {y0, v0};
  double Y2[] = {yfin, vfin};

  int n_steps = 1000;

  double x = xmin;

  int strep_m = int(ceil(n_steps / 2) + 4);

  double dx = (xmax - xmin) / n_steps;

  for (int i = 0; i < strep_m; i++) {
    RK4Step(x, Y1, rhs, dx, 2);
    x += dx;
  }

  x = xmax;
  for (int i = n_steps - 1; i >= strep_m; i--) {
    RK4Step(x, Y2, rhs, dx, 2);
    x -= dx;
  }

  double A = Y1[1] * Y2[0];
  double B = Y1[0] * Y2[1];
  double residual = (A - B) / sqrt(A * A + B * B);
  // double residual = (A - B);
  return residual;
}

int main() {
#if STEP == 0
  ofstream file1;
  file1.open("qho_s1.dat");
  double x0 = exp(-50);
  double v0 = -50 * exp(-50);
  double xfin = exp(-50);
  double Y[] = {x0, v0};
  double xmin = -10;
  double xmax = 10;
  int n_steps = 1000;

  double x = xmin;

  double dx = (xmax - xmin) / n_steps;

  for (int i = 0; i < n_steps; i++) {
    RK4Step(x, Y, rhs, dx, 2);
    x += dx;
    file1 << xmin + i * dx << " " << Y[0] << " " << Y[1] << endl;
  }
#endif

#if STEP == 1
ofstream file1;
file1.open("qho_res.dat");
double step=0.001;
int npoints=5*1000;
  for(int i=0;i<npoints;i++)
  {
    file1 <<i*step<<" "<< residual(i*step) << endl;
  }
  file1.close();
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
