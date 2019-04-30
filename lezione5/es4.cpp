/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 5

  plotting Si(x)
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

int main()
{
  ofstream file;
  file.open("Si_data_2.csv");

  double xmax=25;
  double xmin=0.;
  int n_points=100;
  double dx=(xmax-xmin)/n_points;

  double res=0.;
  double x=0.;

  for(int i=0; i< n_points; i++)
  {
    x=xmin+i*dx;
    res+=gauss(arg_Si, x, x+dx, 5, 3);
    file << x << " "<<res<<endl;
  }
  return 0;
}
