/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 16

  gaussian elimination
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

int main() {
  int n = 5;

  double a[] = {0, 1, 1, 1, 1};
  double b[] = {2, 2, 2, 2, 2};
  double c[] = {1, 1, 1, 1, 1};
  double r[] = {1, 0, 3, 1, 0};

  double *x = new double[n];

  tridiag_solve(a, b, c, r, x, n);

  cout<<"x: ";
  for (int i = 0; i < n; i++) {
    cout << x[i] << " ";
  }
  cout<<endl;
  return 0;
}
