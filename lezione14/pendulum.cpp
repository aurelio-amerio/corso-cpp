/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 14

  pendolo
*/

#include <iostream>
#include "../lib/ode.h"
using namespace std;


void acc(double *Theta, double *res, int n_part)
{
  double g_over_l = 1;

  res[0] = -g_over_l * sin(Theta[0]);

  return;
}




int main() {
  double pi = 3.1415926;
  double Theta[] = {pi/4.};
  double V[] = {0};

  double periodo = 2 * pi;
  double h = 0.1;
  int n_steps = int(ceil(50 * periodo/h));
  return 0;
}
