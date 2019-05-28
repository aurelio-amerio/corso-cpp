/*
  Amerio Aurelio
  Algoritmi numerici per la fisica

  quadratura numerica: implementation
*/

#include "quad.h"

// implementation

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
//
// double simps(double (*func)(double x), double a, double b, double tol) {
//   int n = 2;
//   double res = 0.;
//   double res1 = 0.;
//   while (1) {
//     res = simps(func, a, b, n);
//     res1 = simps(func, a, b, n * 2);
//     if (fabs(res1 - res) < tol) {
//       #if DEBUG
//         cout << "n iter: " << n * 2 << endl;
//       #endif
//       return res1;
//     }
//     n *= 2;
//   }
// }

double gauss_order(double (*func)(double x), double a, double b, int order) {
  // numerical quadrature using Gauusian quadrature with 3 points
  double w_[16];
  double x_[16];
  if (order == 1) {
    w_[0] = 1.;
    w_[1] = 1.;

    x_[0] = -0.5773502691896257;
    x_[1] = -x_[0];
  }

  else if (order == 3) {
    w_[0] = 8. / 9.;
    w_[1] = 5. / 9.;
    w_[2] = -w_[1];

    x_[0] = 0.;
    x_[1] = sqrt(3. / 5.);
    x_[2] = -x_[1];
  }

  else if (order == 4) {
    w_[0] = 0.6521451548625461;
    w_[1] = w_[0];
    w_[2] = 0.3478548451374538;
    w_[3] = -w_[2];

    x_[0] = -0.3399810435848563;
    x_[1] = x_[0];
    x_[2] = -0.8611363115940526;
    x_[3] = -x_[1];
  }

  else if (order == 5) {
    w_[0] = 0.5688888888888889;
    w_[1] = 0.4786286704993665;
    w_[2] = 0.4786286704993665;
    w_[3] = 0.2369268850561891;
    w_[4] = 0.2369268850561891;

    x_[0] = 0.0000000000000000;
    x_[1] = -0.5384693101056831;
    x_[2] = 0.5384693101056831;
    x_[3] = -0.9061798459386640;
    x_[4] = 0.9061798459386640;
  }

  else if (order == 6) {
    w_[0] = 0.3607615730481386;
    w_[1] = 0.3607615730481386;
    w_[2] = 0.4679139345726910;
    w_[3] = 0.4679139345726910;
    w_[4] = 0.1713244923791704;
    w_[5] = 0.1713244923791704;

    x_[0] = 0.6612093864662645;
    x_[1] = -0.6612093864662645;
    x_[2] = -0.2386191860831969;
    x_[3] = 0.2386191860831969;
    x_[4] = -0.9324695142031521;
    x_[5] = 0.9324695142031521;
  } else {
    cout << "order not supported! max 6" << endl;
    return -1;
  }

  double res = 0.;
  double c1 = (b - a) / 2;
  double c2 = (a + b) / 2;

  for (int i = 0; i < order; i++) {
    res += w_[i] * func(c1 * x_[i] + c2);
  }
  res *= c1;
  return res;
}

double gauss(double (*func)(double x), double a, double b, int n_points,
             int order) {
  int n = n_points;
  double dx = (b - a) / n;
  double res = 0.;
  double xa = 0.;
  double xb = 0;
  for (int i = 0; i < n; i++) {
    xa = a + i * dx;
    xb = xa + dx;
    res += gauss_order(func, xa, xb, order);
  }
  return res;
}
//
// double gauss(double (*func)(double x), double a, double b, double tol) {
//   int n = 2;
//   double res = 0.;
//   double res1 = 0.;
//   while (1) {
//     res = gauss(func, a, b, n);
//     res1 = gauss(func, a, b, n * 2);
//     if (fabs(res1 - res) < tol) {
// #if DEBUG
//       cout << "n iter: " << n * 2 << endl;
// #endif
//       return res1;
//     }
//     n *= 2;
//   }
// }
