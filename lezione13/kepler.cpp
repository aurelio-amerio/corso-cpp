/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 13

  keplero
*/

#include "../lib/ode.h"
#include <fstream>
#include <iostream>
using namespace std;

void rhs_1(double t, double *Y, double *R) {
  double x, y, vx, vy, r, v;

  x = Y[0];
  y = Y[1];
  vx = Y[2];
  vy = Y[3];

  r = sqrt(x * x + y * y);
  // v = sqrt(1./r);
  // x = r * cos(theta);
  // y = r * sin(theta);

  R[0] = vx;
  R[1] = vy;
  R[2] = -x / (r * r * r);
  R[3] = -y / (r * r * r);

  return;
}

int main() {
  ofstream file;
  double pi = 3.1415926;

  file.open("orbit.dat");
  double t = 0.;
  double dt = 0.1;
  double dTheta = 0.01;
  int n_steps = int(ceil(2. * pi * 10. / dTheta));
  double v = 0.5;

  double Y[] = {0, 4, v, 0};
  double R[4];
  int orbits = 0;
  double vx1, vx2;
  vx1 = v;

  for (int n = 0; n < n_steps; n++) {
    RK4Step(t, Y, rhs_1, dt, 4);
    dt = dTheta * sqrt(Y[0] * Y[0] + Y[1] * Y[1]) /
         sqrt(Y[2] * Y[2] + Y[3] * Y[3]) t += dt;

    file << Y[0] << " " << Y[1] << endl;
  }
  file.close();
  return 0;
}
