/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 9

  root finder
*/

#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

double func(double x) {
  double res = exp(-x) - x;
  return res;
}

double der(double x) {
  double res = -exp(-x) - 1;
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
    // cout << setprecision(9) << count << " a: " << a << " b: " << b;
    xm = (b + a) / 2.;
    // fa = func(a);
    // fb = func(b);
    fm = func(xm);

    if (fabs(fm) <= ytol || fabs(b - a) <= xtol) {
      // cout << " xm: " << xm << " f(xm): " << fm << endl;
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
    // cout << " xm: " << xm << " f(xm): " << fm << endl;
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
    // cout << setprecision(9) << count << " a: " << a << " b: " << b;
    c1 = (fb - fa) / (b - a);
    c2 = fa - (fb - fa) / (b - a) * a;
    xm = -c2 / c1;
    fm = func(xm);

    if (fabs(fm) <= ytol || fabs(b - a) <= xtol) {
      // cout << " xm: " << xm << " f(xm): " << fm << endl;
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
    // cout << " xm: " << xm << " f(xm): " << fm << endl;
  }
  if (count == 50)
    cout << "exed max num of iterations!" << endl;
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

double newton(double (*func)(double), double (*der)(double), double a, double b,
              double xtol, double ytol) {
  double fx = func(b);
  double f1x = der(b);
  double dx = b - a;
  int k = 1;
  int max_iter = 50;

  double result = 0;
  double dx1 = 0;

  int increase_counter = 0;

  while (k < max_iter) {
    dx1 = fx / f1x;

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

    b = b - dx;
    fx = func(b);
    f1x = der(b);

    if (fabs(dx) <= xtol || fabs(fx) <= ytol) {
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
  cout << "bisec" << endl;
  double res = bisec(func, -1, 1, 1e-7, 1e-7);
  cout << "regula falsi" << endl;
  double res2 = false_pos(func, -1, 1, 1e-7, 1e-7);
  cout << "secant" << endl;
  double res3 = secant(func, -1, 1, 1e-7, 1e-7);
  cout << "newton" << endl;
  double res4 = newton(func, der, -1, 1, 1e-7, 1e-7);
  cout << setprecision(8);
  cout<<endl<<endl;
  cout << "bisec " << res << endl;
  cout << "regula falsi: " << res2 << endl;
  cout << "secant: " << res3 << endl;
  cout << "newton: " << res4 << endl;
  return 0;
}
