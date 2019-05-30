/*
  Amerio Aurelio
  Algoritmi numerici per la fisica

  root finder implementation
*/
#include "root_finders.h"

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
#if DEBUG
      cout << "found root!" << endl;
#endif

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
#if DEBUG
  cout << "iterations= " << count << endl;
#endif
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

  int max_iter = 100;

  while (fabs(b - a) > xtol && count < max_iter) {
    // cout << setprecision(9) << count << " a: " << a << " b: " << b;
    c1 = (fb - fa) / (b - a);
    c2 = fa - (fb - fa) / (b - a) * a;
    xm = -c2 / c1;
    fm = func(xm);

    if (fabs(fm) <= ytol || fabs(b - a) <= xtol) {
// cout << " xm: " << xm << " f(xm): " << fm << endl;
#if DEBUG
      cout << "found root!" << endl;
#endif
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
  if (count == 50) {
    cout << "reached max num of iterations! result is not exact" << endl;
  }
#if DEBUG
  cout << "iterations= " << count << endl;
#endif
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
#if DEBUG
  cout << "root found in " << k << " iterations!" << endl;
#endif
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
#if DEBUG
  cout << "root found in " << k << " iterations!" << endl;
#endif
  return result;
}

void bracket(double (*func)(double), double a, double b, int n_intervals,
             double *xL, double *xR, int &n_roots) {
  double fa = func(a);
  double fb = 0;
  double a0=a;
  n_roots = 0;
  double dx = (b - a) / n_intervals;
  for (int i = 0; i < n_intervals; i++) {
    b = a0 + (i + 1) * dx;
    fb = func(b);
    if ((fb * fa) < 0) {
      xL[n_roots] = a;
      xR[n_roots] = b;
      n_roots++;
    }
    fa = fb;
    a = b;
  }
  return;
}
