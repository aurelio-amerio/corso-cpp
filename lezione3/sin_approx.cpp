/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 3

  series expansion sin(x), non completo
*/

#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

double factorial(int a) {
  // valori non interi verrano troncati
  double res = 1;

  for (int i = 1; i <= a; i++) {
    res = res * i;
  }
  return res;
}

double n_term_sin(int n, double x) {
  int sign = 0;
  if (n % 2 == 0) {
    sign = 1;
  } else {
    sign = -1;
  }
  return sign / factorial(2 * n + 1) * pow(x, 2 * n + 1);
}
double sin(double x) {
  int n = 0;
  double res = 0;
  while (n < 20) {
    double tmp = res+n_term_sin(n,x);
    if (fabs(tmp - res) < 1e-8) {
      break;
    } else {
      res += tmp;
      n++;
    }
  }
  return res;
}

int main() {
  double x = 1;
  cout<<sin(x);
  return 0;
}
