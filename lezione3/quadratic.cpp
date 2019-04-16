/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 3

  *quadratic solver
*/

#include <iostream>
#include <math.h>
using namespace std;

void solve(double a, double b, double c) {
  double x1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
  double x2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
  cout << "x1= " << x1 << endl << "x2= " << x2 << endl;
  return;
}

void solve_v2(double a, double b, double c) {
  double x1 = 0;
  double x2 = 0;
  double delta = b * b - 4 * a * c;

  if (delta < 0) {
    cout << "soluzioni immaginarie!";
    return;
  }

  if (b >= 0) {
    x1 = (-b - sqrt(delta)) / (2 * a);
    x2 = 2 * c / (-b - sqrt(delta));
    cout << "x1= " << x1 << endl << "x2= " << x2 << endl;
  }

  else {
    if (b < 0) {
      x1 = 2 * c / (-b + sqrt(delta));
      x2 = (-b + sqrt(delta)) / (2 * a);
      cout << "x1= " << x1 << endl << "x2= " << x2 << endl;
    }
  }
  // cout << "x1= " << x1 << endl << "x2= " << x2 << endl;
  return;
}

int main() {
  double x1 = 1e-5;
  double x2 = 1e8;
  cout << "x1= " << x1 << " x2= " << x2 << endl;
  double a = 1;
  double b = -(x1 + x2);
  double c = x1 * x2;
  cout << "primo metodo" << endl;
  solve(a, b, c);
  cout << "secondo metodo" << endl;
  solve_v2(a, b, c);
  return 0;
}
