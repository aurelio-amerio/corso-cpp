/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 14

  pendolo
*/

// #include "../lib/ode.h"
#include "ode.h"
#include <iostream>
#include <fstream>
using namespace std;

void acc(double *Theta, double *res, int n_part) {
  static const double g_over_l = 1;

  res[0] = -g_over_l * sin(Theta[0]);

  return;
}

void rhs(double t, double *Y, double *R) {
  double theta, omega;
  static const double g_over_l = 1;

  theta = Y[0];
  omega = Y[1];

  R[0] = omega;
  R[1] = - g_over_l * sin(theta);

  return;
}

int main() {
  ofstream file;
  file.open("pendulum.dat");
  double pi = 3.1415926;
  double Theta[] = {pi / 4.};
  double V[] = {0};

  double periodo = 2 * pi;
  double h = 0.1;
  int n_steps_max = int(ceil(50 * periodo / h))*10;
  double v1, v2;
  int oscillations = 0;

  //velocity verlet
  for (int i = 0; i < n_steps_max; i++) {
    v1 = V[0];
    velocity_Verlet(Theta, V, acc, h, 1, 1);
    file<<i<<" "<<Theta[0]<<" "<<V[0]<<endl;
    // cout<<"theta: "<<Theta[0]<<"\tomega: "<<V[0]<<endl;
    v2 = V[0];
    if (v1 * v2 < 0) {
      oscillations++;
      if (oscillations >= 100) {
        cout << "50 periodi raggiunti!" << endl;
        break;
      }
    }
  }
  file.close();

  //rk 2

  // Runge-Kutta 2
  ofstream file1;
  file1.open("pendulum_rk.dat");
  double Y[] = {pi / 4., 0};
  double t = 0;
  oscillations=0;
  for (int i = 0; i < n_steps_max; i++) {
    v1 = Y[1];
    RKStep(t, Y, rhs, h, 2);
    v2 = Y[1];
    t += h;
    file1 << i << " " << Y[0] << " " << Y[1] << endl;
    if (v1 * v2 < 0) {
      oscillations++;
      if (oscillations >= 100) {
        cout << "50 periodi raggiunti!" << endl;
        break;
      }
    }
  }
  file1.close();

  return 0;
}
