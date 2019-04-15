/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 2

  Calcola il fattoriale
*/

#include <cmath>
#include <iostream>
using namespace std;

unsigned int factorial(unsigned int a) {
  //valori non interi verrano troncati
  if (a < 0 || floor(a) != a) {
    cout << "errore! il valore deve essere un intero positivo";
    return -1;
  }

  else if (a == 1 || a == 0) {
    return 1;
  }

  else {
    return a * factorial(a - 1);
  }
}

int main() // Function Header
{
  unsigned int a = 0;
  cout << "Dammi un numero intero, calcolerò il suo fattoriale!\n";
  cin >> a;
  unsigned int result = factorial(a);
  cout << "Fattoriale di " << a << " = " << result << endl;
  return 0;
}
