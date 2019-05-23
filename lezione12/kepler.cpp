/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 11

  keplero
*/

#include "../lib/ode.h"
#include <iostream>
#include <fstream>
using namespace std;

// void rhs(double theta, double *Y, double *R) {
//   double r, v, xdot, ydot, vxdot, vydot;
//   xdot = Y[0];
//   ydot = Y[1];
//   vxdot = Y[2];
//   vydot = Y[3];
//
//
//   v = sqrt(xdot*xdot + ydot*ydot);
//   r = 1./(v*v);
//   // x = r * cos(theta);
//   // y = r * sin(theta);
//
//   R[0] = v*cos(theta);
//   R[1] = v*sin(theta);
//   R[2] = -cos(theta) / (r*r);
//   R[3] = -sin(theta) / (r*r);
//
//   return;
// }

// void rhs(double theta, double *Y, double *R) {
//   double x, y, vx, vy, r, v;
//   x = Y[0];
//   y = Y[1];
//   vx = Y[2];
//   vy = Y[3];
//
//
//   r = sqrt(x*x+y*y);
//   v = sqrt(1./r);
//   // x = r * cos(theta);
//   // y = r * sin(theta);
//
//   R[0] = v*cos(theta);
//   R[1] = v*sin(theta);
//   R[2] = -x / (r*r*r);
//   R[3] = -y / (r*r*r);
//
//   return;
// }

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
  file.open("orbit.dat");
  double t = 0.;
  double dt = 0.1;
  int n_steps = 1000000;
  double v = 0.5;

  double Y[] = {0, 4, v, 0};
  double R[4];
  int orbits = 0;
  double vx1, vx2;
  vx1 = v;

  for (int n = 0; n < n_steps; n++) {
    vx1 = Y[2];
    RK4Step(t, Y, rhs_1, dt, 4);
    vx2 = Y[2];

    if (vx1 * vx2 < 0) {
      orbits++;
      if (orbits >= 10) {
        cout << "ho fatto 10 orbite!" << endl;
        break;
      }
    }
    t += dt;
    cout << "r " << sqrt(Y[0] * Y[0] + Y[1] * Y[1]) << "\tx " << Y[0] << "\ty "
         << Y[1] << endl;
    file<<Y[0]<<" "<<Y[1]<<endl;
  }
  file.close();
  return 0;
}
