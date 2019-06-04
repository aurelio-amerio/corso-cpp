/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 16

  relaxation ode solving
*/
#include <iostream>
#include <math.h>
using namespace std;

void tridiag_solve(double *a, double *b, double *c, double *r, double *x,
                   int n) {
  double *h = new double[n];
  double *p = new double[n];

  for (int i = 0; i < n; i++) {
    if (i == 0) {
      h[i] = c[i] / b[i];
      p[i] = r[i] / b[i];
    } else {
      h[i] = c[i] / (b[i] - a[i] * h[i - 1]);
      p[i] = (r[i] - a[i] * p[i - 1]) / (b[i] - a[i] * h[i - 1]);
    }
    for (int i = n - 1; i >= 0; i--) {
      if (i == (n - 1)) {
        x[i] = p[i];
      } else {
        x[i] = p[i] - h[i] * x[i + 1];
      }
    }
  }

  delete h;
  delete p;
  return;
}
//TODO: finire
void relaxationSolve(double (*func)(double x), double *Y, double xmin,
                     double xmax, int n) {
  double dx = (xmax - xmin) / n;
  double alpha = Y[0];
  double beta = Y[n - 1];
  double *x = new double[n - 3];

  double *r = new double[n - 2];

  r[0] = dx * dx * func(x + dx) - alpha;
  r[n - 3] = dx * dx * func(xmax - dx) - beta;
  for (int i = 0; i < n - 4; i++) {
    x[i] = x + (i+2) * dx;
    r[i] = dx * dx * func(x[i]);
  }

  double *a = new double[n - 3];
  double *b = new double[n - 3];
  double *c = new double[n - 3];


  double *res = new double[n-3];

  for(int i=0; i<n-3; i++)
  {
    if(i==0)
    {
      a[i]=0;
      b[i]=-2;
      c[i]=1;
    }
    else if(i==n-4)
    {
      a[i]=1;
      b[i]=-2;
      c[i]=0;
    }
    else
    {
      a[i]=1;
      b[i]=-2;
      c[i]=1;
    }
  }
  tridiag_solve(a,b,c,r,x,n-2);
  return 0;
}

int main() {



  tridiag_solve(a, b, c, r, x, n);

  cout << "x: ";
  for (int i = 0; i < n; i++) {
    cout << x[i] << " ";
  }
  cout << endl;
  return 0;
}
