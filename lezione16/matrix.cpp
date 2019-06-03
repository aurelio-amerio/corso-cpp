#include <iostream>
using namespace std;

void func(double **A, double *b, int n) {
  double res = 0;
  for (int i = 0; i < n; i++) {
    res = 0;
    for (int j = 0; j < n; j++) {
      res += A[i][j] * b[j];
      cout << res << " ";
    }
    cout << endl;
  }
  return;
}

int main() {
  int rows = 0;
  cout << "rows: ";
  cin >> rows;
  int cols = rows;

  double *b = new double[rows];

  for (int i = 0; i < rows; i++)
    b[i] = i;

  double **matrix = new double *[rows];
  if (rows) {
    matrix[0] = new double[rows * cols];
    for (int i = 1; i < rows; ++i)
      matrix[i] = matrix[0] + i * cols;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = i * j;
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << "\nprint matrix:\n";
  func(matrix, b, rows);

  // delete matrix
  if (rows)
    delete[] matrix[0];
  delete[] matrix;

  //delete b
  delete b;

  // return
  return 0;
}
