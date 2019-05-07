/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 8

  root finder: bisection
*/

#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

double func(double x) {
  double res = exp(-x) - x;
  return res;
}

double Bisection(double (*func)(double), double a, double b, double tol) {
  // double error = 1.;
  double fa = func(a);
  double fb = func(b);
  double xm = 0.;
  double fm = 0.;
  if (fa * fb > 0) {
    cout << "fa*fb must be <= 0!";
    return 0;
  }

  // if (fabs(fa) < tol)
  //   return a;
  // if (fabs(fb) < tol)
  //   return b;

  int lim = 1000;
  int count = 1;

  while (fabs(b - a) > tol) {
    cout << setprecision(9) << count <<" a: " << a << " b: " << b;
    xm = (b + a) / 2.;
    // fa = func(a);
    // fb = func(b);
    fm = func(xm);

    if (fabs(fm) <= tol) {
      cout << " xm: " << xm << " f(xm): " << fm << endl;
      cout << "found root!" << endl;

      break;
    } else if ((fa * fm) < 0) {
      b = xm;
      fb = fm;
      count++;
    } else if ((fa * fm) > 0) {
      a = xm;
      fa = fa;
      count++;
    }
    cout << " xm: " << xm << " f(xm): " << fm << endl;
  }
  cout << "iterations= " << count << endl;
  return xm;
}

int main() // Function Header
{
  double res = Bisection(func, -1, 1, 1e-7);
  cout << setprecision(12) << res << endl;
  return 0;
}
