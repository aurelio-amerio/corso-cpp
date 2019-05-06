/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 7

  pi
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
  unsigned int n_points = 0;
  unsigned int n_in = 0;

  double tol = 1e-4;
  int nmax = 1e7;
  int nmin = 1;
  int n_steps = 1000;
  int log_step = ceil((log10(nmax) - log10(nmin)) / n_steps);

  double res = 0.;
  int n_interval = 0;

  double x;
  double y;

  for (int j = 0; j < n_steps; j++) {
    n_interval = ceil(pow(10, j * log_step));
    cout<<n_interval
    n_points += n_interval;

    for (int i = 0; i < n_interval; i++) {
      x = (drand48() - 0.5) * 2.;
      y = (drand48() - 0.5) * 2.;
      if ((x * x + y * y) < 1)
        n_in += 1;
    }
    res = 4. * double(n_in) / double(n_points);
    double error = fabs(res - pi);
    double error_theo = 1. / sqrt(n_points);

    file1 << n_points << " " << error << endl;
    file2 << n_points << " " << error_theo << endl;
  }
  cout << "pi: " << setprecision(4) << res << endl;
  return 0;
}
