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

double simps(double (*func)(double x), double a, double b, double tol = 1e-5,
             bool verbose = false) {
  int n = 2;
  double res = 0.;
  double res1 = 0.;
  while (1) {
    res = simps(func, a, b, n);
    res1 = simps(func, a, b, n * 2);
    if (fabs(res1 - res) < tol) {
      if (verbose == true) {
        cout << "n iter: " << n * 2 << endl;
      }
      return res1;
    }
    n *= 2;
  }
}

double gauss_3(double (*func)(double x), double a, double b) {
  // numerical quadrature using Gauusian quadrature with 3 points
  static double w_[] = {8. / 9., 5. / 9., 5. / 9.};
  static double x_[] = {0., sqrt(3. / 5.), -sqrt(3. / 5.)};

  double res = 0.;
  double c1 = (b - a) / 2;
  double c2 = (a + b) / 2;

  for (int i = 0; i < 3; i++) {
    res += w_[i] * func(c1 * x_[i] + c2);
  }
  res *= c1;
  return res;
}

double gauss(double (*func)(double x), double a, double b, int n_points) {
  int n = n_points;
  double dx = (b - a) / n;
  double res = 0.;
  double xa = 0.;
  double xb = 0;
  for (int i = 0; i < n; i++) {
    xa = a + i * dx;
    xb = xa + dx;
    res += gauss_3(func, xa, xb);
  }
  return res;
}

double gauss(double (*func)(double x), double a, double b, double tol = 1e-5,
             bool verbose = false) {
  int n = 2;
  double res = 0.;
  double res1 = 0.;
  while (1) {
    res = gauss(func, a, b, n);
    res1 = gauss(func, a, b, n * 2);
    if (fabs(res1 - res) < tol) {
      if (verbose == true) {
        cout << "n iter: " << n * 2 << endl;
      }
      return res1;
    }
    n *= 2;
  }
}
