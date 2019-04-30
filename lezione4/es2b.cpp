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

double func(double x) { return sqrt(1 + x); }
double int_func(double a, double b) { return -exp(-b) + exp(-a); }

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

double gauss(double (*func)(double x), double a, double b, double tol = 1e-5, bool verbose=false) {
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

// double test_conv(double (*func)(double (*arg)(double x), double a, double b,
//                                 int n),
//                  double (*arg)(double x), double a, double b, double tol =
//                  1e-5, double n0 = 2) {
//   int n = n0;
//   double res = 0.;
//   double res1 = 0.;
//
//   while (1) {
//     res = func(arg, a, b, n);
//     res1 = func(arg, a, b, n * 2);
//     if (fabs(res1 - res) < tol) {
//       break;
//     }
//     n = n * 2;
//   }
//
//   return n;
// }

int main() // Function Header
{
  double a = 0.;
  double b = 1.;
  int n = 2;
  cout << "dammi a, b: ";
  cin >> a >> b;
  cout << setprecision(12);
  cout << gauss(func, a, b, 1e-5) << endl;
  cout << simps(func, a, b, 1e-5) << endl;

  return 0;
}
