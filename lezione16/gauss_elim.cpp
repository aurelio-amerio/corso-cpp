/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 16

  gaussian elimination
*/

void swapRowsMatrix(double **A, int r1, int r2) {
  double *A_r1 = A[r1];
  A[r1] = A[r2];
  A[r2] = A_r1;
}

void swapRowsVector(double *b, int r1, int r2) {
  double b_r1 = b[r1];
  b[r1] = b[r2];
  b[r2] = b_r1;
}

#include <iostream>
#include <math.h>
using namespace std;

void gaussian_elim(double **A, double *b, double *x, double n) {

  for (int k = 0; k < n - 1; k++) {

    for (int i = k + 1; i < n; i++) {
      if (A[k][k] == 0) {
        // find the index of the row containing the maximum value
        int jmax = k;
        double A_max = fabs(A[jmax][k]);
        for (int j = k + 1; j < n; j++) {
          if (fabs(A[j][k]) > A_max) {
            jmax = j;
            A_max = fabs(A[jmax][k]);
          }
        }

        // swap rows
        // mem location of old A[k]
        swapRowsMatrix(A, k, jmax);
        swapRowsVector(b, k, jmax);
      }
      double m = A[i][k] / A[k][k];
      for (int j = k + 1; j < n; j++) {
        A[i][j] -= m * A[k][j];
      }
      A[i][k] = 0.0;
      b[i] -= m * b[k];
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    double tmp = b[i];
    for (int j = n - 1; j > i; j--) {
      tmp -= x[j] * A[i][j];
    }
    x[i] = tmp / A[i][i];
  }

  return;
}

int main() {
  double A_tmp[4][4] = {
      {1, 2, 1, -1}, {3, 6, 4, 4}, {4, 4, 3, 4}, {2, 0, 1, 5}};
  int n = 4;

  double **A = new double *[n];
  if (n) {
    A[0] = new double[n * n];
    for (int i = 1; i < n; ++i)
      A[i] = A[0] + i * n;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      A[i][j] = A_tmp[i][j];
    }
  }

  double b[] = {5, 16, 22, 15};
  double *x = new double[n];

  gaussian_elim(A, b, x, n);

  for (int i = 0; i < n; i++) {
    cout << x[i] << endl;
  }

  return 0;
}
