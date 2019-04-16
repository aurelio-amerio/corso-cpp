/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 3

  Esempi di roundoff
*/

#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

double sqrt_babyl(double s, double s0, double tol=1e-5) {
  double res = s0;

  int n = 0;
  while (n < 1000) {
    double tmp = (res + s / res) / 2;
    if (fabs(tmp - res)/res < tol) {
      res = tmp;
      return res;
    } else {
      res = tmp;
      n++;
    }
  }
  cout<<"l'algoritmo non è arrivato a convergere in 1000 iterazioni";
  return -1;
}

int main() {
  double s, s0;
  double tol=1e-8;
  cout << " dammi s e s0: ";
  cin >> s >> s0;
  cout << endl << "sqrt(s)= " << setprecision(14)<<sqrt_babyl(s, s0, tol)<<"+-"<<tol<<endl;
  cout <<"valore 'vero': "<<sqrt(s)<<endl;
  return 0;
}
