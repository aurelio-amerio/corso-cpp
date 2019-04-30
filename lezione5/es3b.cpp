/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 5

  Si(x)
*/

#include "../lib/quad.h"
#include <iostream>
#include <fstream>
using namespace std;

double arg_Si(double x) { return sin(x) / x; }

double Si(double x, int n_intervals, int order=5) {
  int n = n_intervals;
  if (x < 0) {
    cout << "x must be >=0";
    return -1;
  } else if (fabs(x - 0) < 1e-9) {
    return x;
  } else {
    return gauss(arg_Si, 0., x, n, order);
  }
}

double Si(double x, double tol=1e-8) {
  if (x < 0) {
    cout << "x must be >=0";
    return -1;
  } else if (fabs(x - 0) < 1e-9) {
    return x;
  } else {
    return gauss(arg_Si, 0., x, tol);
  }
}

double Si_mid(double x, int n_intervals) {
  int n = n_intervals;
  if (x < 0) {
    cout << "x must be >=0";
    return -1;
  } else if (fabs(x - 0) < 1e-9) {
    return 0.;
  } else {
    return mid_quad(arg_Si, 0., x, n);
  }
}

int main()
{
  ofstream file;
  file.open ("test.csv");
  double dx=3./100.;
  double x=0.;
  file<<setprecision(12);
  file<<"x,sin(x)/x"<<endl;
  for(int i=0; i<100; i++)
  {
    x=1e-8+i*dx;
    file<<x<<","<<arg_Si(x)<<endl;
  }

  file.close();
  return 0;
}
