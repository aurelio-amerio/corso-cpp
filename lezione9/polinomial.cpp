/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione #

  *nome dell'esecizio*
*/
#include "../lib/root_finders.h"

double func(double x) {
  static int n = 4;
  static double a[] = {5., 1., -3., 1.};

  double p = a[n];
  double dpdx = 0;

  for (int j = n - 1; j >= 0; j--) {
    dpdx = dpdx * x + p;
    p = p * x + a[j];
  }
  return p;
}

double derivative(double x) {
  static int n = 4;
  static double a[] = {5., 1., -3., 1.};

  double p = a[n];
  double dpdx = 0;

  for (int j = n - 1; j >= 0; j--) {
    dpdx = dpdx * x + p;
    p = p * x + a[j];
  }
  return dpdx;
}

int main() // Function Header
{
  double res = func(3);
  double der = derivative(3);

  double a = -2;
  double b = 0;
  double xtol = 1e-8;
  double ytol = 1e-8;

  cout << "bisec" << endl;
  double res_bisec = bisec(func, a, b, xtol, ytol);
  cout << "x: " << res_bisec << endl << endl;
  cout << "false position" << endl;
  double res_fp = false_pos(func, a, b, xtol, ytol);
  cout << "x: " << res_fp << endl << endl;
  cout << "secant" << endl;
  double res_secant = secant(func, a, b, xtol, ytol);
  cout << "x: " << res_secant << endl << endl;
  cout << "newton" << endl;
  double res_newton = newton(func, derivative, a, b, xtol, ytol);
  cout << "x: " << res_newton << endl << endl;

#if DEBUG
  cout << "DEBUG" << endl;
#endif

  return 0;
}
