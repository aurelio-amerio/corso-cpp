/*
  operazioni con interi
*/

#include <iostream>
using namespace std;

int divisione_interi(int a, int b) {
  // prende due numeri interi a e b e ritrona a/b intero
  return a / b;
}

double divisione_double(int a, int b) {
  // prende due numeri interi a e b e ritrona a/b intero
  return (double)a / (double)b;
}

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
  d = divisione_interi(a, b);
  cout << "divisione intera a/b=" << d << endl;

  // casting divisione tra interi -> double
  d = divisione_double(a, b);
  cout << "divisione double a/b=" << d << endl;

  return 0;
}
