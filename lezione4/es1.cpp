/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 4

  quadratura numerica
*/

#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

double func(double x) { return exp(-x); }
double int_func(double a, double b) { return -exp(-b) + exp(-a); }

double rect_quad(double (*func)(double x), double a, double b, int n) {
  // numerical quadrature using rectangular rule
  double dx = (b - a) / double(n);
  double res = 0.;
  double x;
  for (int i = 0; i < n; i++) {
    x = a + dx * (double(i));
    res += func(x);
  }
  res = res * dx;
  return res;
}

double mid_quad(double (*func)(double x), double a, double b, int n) {
  // numerical quadrature using midpoint rule
  double dx = (b - a) / double(n);
  double res = 0.;
  double x;
  for (int i = 0; i < n; i++) {
    x = a + dx * (double(i) + 0.5);
    res += func(x);
  }
  res = res * dx;
  return res;
}

double trapz(double (*func)(double x), double a, double b, int n) {
  // numerical quadrature using trapezioidal rule
  double dx = (b - a) / double(n);
  double res = func(a) / 2.;
  double x;

  for (int i = 1; i < n; i++) {
    x = a + dx * i;
    res += func(x);
  }
  res += func(b) / 2.;
  res = res * dx;
  return res;
}

double simps(double (*func)(double x), double a, double b, int n) {
  // numerical quadrature using Simpson rule
  if (n % 2 != 0) {
    cout << "must use an even number of intervals n";
    return -1.;
  }
  double dx = (b - a) / double(n);
  double res = func(a);
  double w = 4.;
  double x = 0.;

  for (int i = 1; i < n; i++) {
    x = a + dx * i;
    res += func(x) * w;
    w = 6. - w;
  }
  res += func(b);
  return res * dx / 3.;
}

double test_conv(double (*func)(double (*arg)(double x), double a, double b,
                                int n),
                 double (*arg)(double x), double a, double b, double tol = 1e-5,
                 double n0 = 2) {
  int n = n0;
  double res = 0.;
  double res1 = 0.;

  while (1) {
    res = func(arg, a, b, n);
    res1 = func(arg, a, b, n * 2);
    if (fabs(res1 - res) < tol) {
      break;
    }
    n = n * 2;
  }

  return n;
}

int main() // Function Header
{
  double a = 0.;
  double b = 1.;
  int n = 100;
  cout << "dammi a, b, n: ";
  cin >> a >> b >> n;
  cout << "resut rect_quad= " << setprecision(12) << rect_quad(func, a, b, n)
       << endl;
  cout << "resut mid_quad= " << setprecision(12) << mid_quad(func, a, b, n)
       << endl;
  cout << "resut trapz= " << setprecision(12) << trapz(func, a, b, n) << endl;
  cout << "resut simps= " << setprecision(12) << simps(func, a, b, n) << endl;
  cout << "resut correct= " << setprecision(12) << int_func(a, b) << endl;

  cout << endl << "testing convergence speed" << endl;
  double tol = 1e-5;
  cout << "set tollerance: ";
  cin >> tol;

  cout << "steps required for convergence (rect_quad): "
       << test_conv(rect_quad, func, a, b, tol) << endl;
  cout << "steps required for convergence (trapz): "
       << test_conv(trapz, func, a, b, tol) << endl;
  cout << "steps required for convergence (mid_quad): "
       << test_conv(mid_quad, func, a, b, tol) << endl;
  cout << "steps required for convergence (simps): "
       << test_conv(simps, func, a, b, tol) << endl;
  return 0;
}
