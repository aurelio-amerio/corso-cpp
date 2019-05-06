/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 6

  prn_uniformity
*/

#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

double error(int n_points, int k) {
  double temp;
  double res=0;

  for (int i = 0; i < n_points; i++) {
    temp = drand48();
    res += pow(temp, k);
  }

  res /= n_points;

  double theo = 1. / (1 + k);
  double relative_error = abs(theo - res);

  return relative_error;
}

int main() // Function Header
{
  ofstream file;
  file.open("error.dat");

  srand48(time(NULL));
  int k = 2;

  int dn = 100;
  int nmin = 10;
  int nmax = 1e4;
  for (int i = nmin; i = nmax; i += dn) {
    file << i << " " << error(i, k) << endl;
  }

  file.close();
  return 0;
}
