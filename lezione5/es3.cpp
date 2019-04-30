/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 5

  Si(x)
*/

#include "../lib/quad.h"
#include <iostream>
using namespace std;

double arg_Si(double x) { return sin(x) / x; }

double Si(double x, int n_intervals) {
  int n = n_intervals;
  if (x < 0) {
    cout << "x must be >=0";
    return -1;
  } else if (fabs(x - 0) < 1e-9) {
    return x;
  } else {
    return gauss(arg_Si, 0., x, n);
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
  int n_int=0;
  double x=0.8;
  cout<<"x: ";
  cin>>x;
  cout<<"n intervals: ";
  cin>>n_int;
  cout<<setprecision(12);
  cout <<"mid: "<< Si_mid(x, n_int) << endl;
  cout <<"gauss: "<< Si(x, n_int) << endl;
  cout <<"true value: "<< Si(x, 1e-9) << endl;
  return 0;
}
