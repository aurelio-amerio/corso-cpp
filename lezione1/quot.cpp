/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 1

  Quotient
*/

#include <iostream>
using namespace std;

int *Quot(int, int);

int main() {
  int a, b;
  cout << "dammi due valori: ";
  cin >> a >> b;
  int *result;
  result = Quot(a, b);
  cout << "quot= " << result[0] << " remainder= " << result[1] << endl;
  return 0;
}

int *Quot(int a, int b) {
  int quotient = a / b;
  int remainder = a % b;
  static int res[] = {quotient, remainder};
  return res;
}
