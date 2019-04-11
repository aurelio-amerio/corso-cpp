/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 1

  Quotient
*/

#include <iostream>
using namespace std;

int Sum(int, int);

int main() // Function Header
{
  int a = 1;
  int b = 3;
  int c = Sum(1, 3);
  cout << c << endl;
  return 0;
}

int Sum(int a, int b) { return a + b; }
