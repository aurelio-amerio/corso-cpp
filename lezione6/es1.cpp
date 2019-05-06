/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 6

  integrali doppi
*/

#include "../lib/quad.h"
#include <iostream>
#include <math.h>
using namespace std;

double func(double x, double y) {
  return x * x * x * x * y * y + 2 * y * y * x * x - y * x * x + 2;
}

double func2(double x, double y) {
  if (sqrt(x * x + y * y) <= 1)
    return 1;
  else
    return 0;
}

int main() // Function Header
{
  double pi = 3.1415926;

  int n = 8;
  double res = 0.;
  double tol = 1e-5;

  while (1) {
    res = gauss_2d(func2, -1, 1, -1, 1, n, n, 6);
    // cout << "n iter: " << n << endl;
    // cout<<res<<endl;
    if (abs(pi - res) < tol) {
        break;
    }
    n *= 2;
  }
  cout << "n iter total: " << n << endl;

  //
  // double res1 = gauss_2d(func2, -1., 1., -1., 1., 1000, 1000, 6);
  cout << setprecision(12);
  cout << "pi: " << pi << endl << "res: " << res << endl;
  return 0;
}
// now I need a drink, alcoholic of course
// 3.1415926
