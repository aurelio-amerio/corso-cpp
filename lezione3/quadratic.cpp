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
int main() 
{

  double x1 = 1e-12;
  double x2 = 1e12;
  cout<<"x1= "<<x1<<" x2= "<<x2<<endl;
  double a = 1;
  double b = -(x1 + x2);
  double c = x1 * x2;
  solve(a, b, c);

  return 0;
}
