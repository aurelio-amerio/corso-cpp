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

double error(int n_points, int k)
{
  double temp;

  for (int i = 0; i < n_points; i++) {
    temp = drand48();
    file << i << " " << temp << endl;
    res += pow(temp, k);
  }

  res /= n_points;

  double theo = 1. / (1 + k);
  double relative_error=abs(theo-res);

  return relative_error;
}

int main() // Function Header
{
  ofstream file;
  file.open("random.dat");
  srand48(time(NULL));
  int n_points = 1000;

  cout << "n points: ";
  cin >> n_points;
  double res = 0.;
  int k = 0;

  cout << "dammi un k: ";
  cin >> k;

  double temp;

  for (int i = 0; i < n_points; i++) {
    temp = drand48();
    file << i << " " << temp << endl;
    res += pow(temp, k);
  }

  res /= n_points;

  double theo = 1. / (1 + k);

  cout << "res: " << res << endl;
  cout << "theoretical value: " << theo << endl;
  cout << "relative error: " << abs(res - theo) / theo << endl;
  file.close();
  return 0;
}
