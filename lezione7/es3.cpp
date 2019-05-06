/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 7

  exponential decay
*/

#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

bool do_decay(double lambda = 0.01) {
  double res = drand48();
  if (res > lambda)
    return false;
  else
    return true;
}

int exp_decay(int n0, int t, double lambda = 0.01) {
  double res = double(n0) * exp(-lambda * t);
  return floor(res);
}

int main() // Function Header
{
  ofstream file;
  file.open("rand_decay.dat");
  double lambda = 0.01;
  srand48(time(NULL));
  int n0 = 1000; // number of particles
  int Np=n0;
  int t = 0;

  file << t << " " << Np << endl;

  while (Np > 0) {
    int dN = 0; // number of decays
    for (int i = 0; i < Np; i++) {
      if (do_decay(lambda) == true)
        dN++;
    }
    Np -= dN;
    t++;
    file << t << " " << Np << endl;
  }
  file.close();

  // create exponential data for reference
  ofstream file2;
  file2.open("exp_decay.dat");

  for (int i = 0; i < t; i++) {
    double res = exp_decay(n0, i, lambda);
    file2 << i << " " << res << endl;
  }
  file2.close();
  return 0;
}
