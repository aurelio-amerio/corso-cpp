/*
  operazioni con interi
*/

#include <iostream>
using namespace std;

int main() {
  int a = 1;
  int b = 3;
  int c = 0;
  double d = 0;

  // addizione
  c = a + b;
  cout << "a+b=" << c << endl;

  // sottrazio
  c = a - b;
  cout << "a-b=" << c << endl;

  // moltiplicazione
  c = a * b;
  cout << "a*b=" << c << endl;

  // divisione tra interi
  d = a / b;
  cout << "divisione intera a/b=" << d << endl;

  // casting divisione tra interi -> double
  d = (double)a / b;
  cout << "divisione double a/b=" << d << endl;

  return 0;
}
