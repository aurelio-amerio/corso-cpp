#include "derivatives.h"
#include <fstream>
#include <iomanip>
#include <string>

double euler(double (*dydx)(double x, double y), double x, double y0,
             double h) {
  double result = y0;
  int n_steps = int(ceil(x / h));
  // cout<<"n steps: "<<n_steps<<endl;
  double t = 0.;
  for (int i = 0; i < n_steps; i++) {
    t = h * i;
    result += h * dydx(t, result);
  }
  return result;
}

double euler_print(double (*dydx)(double x, double y),
                   double (*exact)(double x), double x, double y0, double h,
                   string file_name) {
  ofstream file;
  file.open(file_name);

  double result = y0;
  int n_steps = int(ceil(x / h));
  // cout<<"n steps: "<<n_steps<<endl;
  double t = 0.;
  double abs_err = 0.;
  double relative_err = 0.;
  file << setprecision(10)<< t << " " << result << " " << abs_err << " " << relative_err << endl;
  for (int i = 1; i <= n_steps; i++) {
    result += h * dydx(t, result);
    t = h * i;
    abs_err = fabs(result - exact(t));
    relative_err = fabs((result - exact(t)) / exact(t));
    file << setprecision(10)<< t << " " << result << " " << abs_err << " " << relative_err << endl;
  }
  file.close();
  return result;
}

double dydx(double x, double y) { return -x * y; }

double exact(double x) { return exp(-x * x / 2); }

int main() {
  double x = 3;
  double h = 0.25;
  double y0 = 1.;
  // cout << "solution: " << euler(dydx, x, y0, h)<<endl;
  // cout << "exact: " << exact(x)<<endl;
  euler_print(dydx, exact, x, y0, 0.5, "ode05.dat");
  euler_print(dydx, exact, x, y0, 0.25, "ode025.dat");
  euler_print(dydx, exact, x, y0, 0.1, "ode01.dat");
  euler_print(dydx, exact, x, y0, 0.01, "ode001.dat");
  return 0;
}
