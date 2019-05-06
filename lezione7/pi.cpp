/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 7

  pi
*/

#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

int main() // Function Header
{
  double pi = 3.1415826;
  srand48(time(NULL));
  unsigned int n_points = 0;
  // cout << "n points: ";
  // cin >> n_points;
  double x;
  double y;
  unsigned int n_in = 0;
  // for (int i = 0; i < n_points; i++) {
  //   x = (drand48() - 0.5) * 2.;
  //   y = (drand48() - 0.5) * 2.;
  //   if (x * x + y * y < 1)
  //     n_in += 1;
  // }
  // double res = 4. * double(n_in) / double(n_points);
  // cout << "pi: " << res << endl;
  // cout << "true pi: " << pi << endl;

  // compute how many cicles it takes to reach a tollerance of 1e-5
  double tol = 1e-5;
  int n_step = 100;
  n_points = 100;
  n_in = 0;
  double res2 = 0.;
  int n_iter = 0;
  while (1) {
    n_points += n_step;
    for (int i = 0; i < n_step; i++) {
      x = (drand48() - 0.5) * 2.;
      y = (drand48() - 0.5) * 2.;
      if (x * x + y * y < 1)
        n_in += 1;
    }
    res2 = 4. * double(n_in) / double(n_points);
    if (abs(res2 - pi) < tol) {
      break;
    } else if (n_iter > 1e8) {
      cout << "max iter reached!" << endl;
      break;
    } else
      n_iter++;
  }
  cout << "pi with tollerance = " << tol << " found in " << n_iter
       << " iterations!" << endl;
  cout << "pi: " << res2 << endl;
  return 0;
}
