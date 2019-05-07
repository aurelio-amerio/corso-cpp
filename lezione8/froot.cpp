/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 8

  root finder: bisection + regula falsi
*/

#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

double func(double x) {
  double res = exp(-x) - x;
  return res;
}

double bisec(double (*func)(double), double a, double b, double xtol,
             double ytol) {
  // double error = 1.;
  double fa = func(a);
  double fb = func(b);
  double xm = 0.;
  double fm = 0.;
  if (fa * fb > 0) {
    cout << "fa*fb must be <= 0!";
    return 0;
  }

  int lim = 1000;
  int count = 1;

  int max_iter = 50;

  while (fabs(b - a) > xtol && count < max_iter) {
    cout << setprecision(9) << count << " a: " << a << " b: " << b;
    xm = (b + a) / 2.;
    // fa = func(a);
    // fb = func(b);
    fm = func(xm);

    if (fabs(fm) <= ytol || fabs(b - a) <= xtol) {
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

double false_pos(double (*func)(double), double a, double b, double xtol,
                 double ytol) {
  // double error = 1.;
  double fa = func(a);
  double fb = func(b);
  double xm = 0.;
  double fm = 0.;
  if (fa * fb > 0) {
    cout << "fa*fb must be <= 0!";
    return 0;
  }

  int lim = 1000;
  int count = 1;

  double c1 = 0;
  double c2 = 0;

  int max_iter = 50;

  while (fabs(b - a) > xtol && count < max_iter) {
    cout << setprecision(9) << count << " a: " << a << " b: " << b;
    c1 = (fb - fa) / (b - a);
    c2 = fa - (fb - fa) / (b - a) * a;
    xm = -c2 / c1;
    fm = func(xm);

    if (fabs(fm) <= ytol || fabs(b - a) <= xtol) {
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
  if (count == 50)
    cout << "iterations= " << count << endl;
  return xm;
}

double secant(double (*func)(double), double a, double b, double xtol,
              double ytol) {
  double fa = func(a);
  double fb = func(b);
  double dx = b - a;
  int k = 1;
  int max_iter = 50;

  double result = 0;
  double dx1 = 0;

  int increase_counter = 0;

  while (k < max_iter) {
    dx1 = fb * (b - a) / (fb - fa);

    if (fabs(dx1) < fabs(dx)) {
      dx = dx1;
      increase_counter = 0;
    } else {
      increase_counter++;
    }
    if (increase_counter > 10) {
      cout << "dx increased for 10 intervals! consider using bisection!"
           << endl;
      return 0;
    }
    a = b;
    fa = fb;
    b = b - dx;
    fb = func(b);
    if (fabs(dx) <= xtol || fabs(fb) <= ytol) {
      result = b;
      break;
    }
    k++;
  }
  cout << "root found in " << k << " iterations!" << endl;
  return result;
}

int main() // Function Header
{
  double res = bisec(func, -1, 1, 1e-7, 1e-7);
  double res2 = false_pos(func, -1, 1, 1e-7, 1e-7);
  double res3 = secant(func, -1, 1, 1e-7, 1e-7);
  cout << setprecision(12);
  cout << "bisec " << res << endl;
  cout << "regula falsi: " << res2 << endl;
  cout << "secant: " << res3 << endl;
  return 0;
}
