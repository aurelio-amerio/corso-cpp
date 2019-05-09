/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione #

  *nome dell'esecizio*
*/
#include "../lib/root_finders.h"

double func(double x) {
  double result = sin(x) - ((x / 10.) * (x / 10.) + x / 5. + 1. / 3.);
  return result;
}

double derivative(double x) {
  double result = cos(x) - ((1. / 5.) * (x / 10.) + 1. / 5.);
  return result;
}

int main() {
  int n_intervals = 100;
  double a = -10.;
  double b = 10.;
  double xtol = 1e-8;
  double ytol = 1e-8;

  int n_roots = 0;
  double xL[10];
  double xR[10];

  bracket(func, a, b, n_intervals, xL, xR, n_roots);
  cout << "n roots: " << n_roots << endl;
  cout << setprecision(9);
  for (int i = 0; i < n_roots; i++) {
    cout << "#" << i << " " << newton(func, derivative, xL[i], xR[i], xtol, ytol)
         << endl;
  }
  // cout << "bisec" << endl;
  // double res_bisec = bisec(func, a, b, xtol, ytol);
  // cout << "x: " << res_bisec << endl << endl;
  // cout << "false position" << endl;
  // double res_fp = false_pos(func, a, b, xtol, ytol);
  // cout << "x: " << res_fp << endl << endl;
  // cout << "secant" << endl;
  // double res_secant = secant(func, a, b, xtol, ytol);
  // cout << "x: " << res_secant << endl << endl;
  // cout << "newton" << endl;
  // double res_newton = newton(func, derivative, a, b, xtol, ytol);
  // cout << "x: " << res_newton << endl << endl;

  return 0;
}
