/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 7

  pi plot version
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

int main() // Function Header
{
  ofstream file1;
  ofstream file2;
  file1.open("error_empirical.dat");
  file2.open("error_theo.dat");

  double pi = 3.1415826;
  srand48(time(NULL));
  unsigned int n_points = 10;
  double x;
  double y;
  unsigned int n_in = 0;
  double tol = 1e-4;
  int n_step = 10;

  double res2 = 0.;
  int n_iter = 0;
  int n_iter_max = 100;
  while (n_iter < n_iter_max) {

    for (int i = 0; i < n_step; i++) {
      x = (drand48() - 0.5) * 2.;
      y = (drand48() - 0.5) * 2.;
      if ((x * x + y * y) < 1)
        n_in += 1;
    }

    res2 = 4. * double(n_in) / double(n_points);
    double error = fabs(res2 - pi);
    double error_theo = 1. / sqrt(n_points);

    file1 << n_points << " " << error << endl;
    file2 << n_points << " " << error_theo << endl;

    n_iter++;
    n_step=n_points*2-n_pounts;
    n_points *= 2;
  }

  cout << "pi with tollerance = " << tol << " found in " << n_iter
       << " iterations!" << endl;
  cout << "pi: " << setprecision(4) << res2 << endl;
  return 0;
}
