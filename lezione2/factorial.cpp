/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 2

  Calcola il fattoriale
*/

<<<<<<< HEAD
#include <iostream>
#include <math.h>
using namespace std;

unsigned int factorial(unsigned int a) {
  // valori non interi verrano troncati
=======
#include <cmath>
#include <iostream>
using namespace std;

unsigned int factorial(unsigned int a) {
  //valori non interi verrano troncati
>>>>>>> 720b9df4d943c1e9538749956131d53c544c2ddb
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

<<<<<<< HEAD
double factorial_for(int a) {
  // valori non interi verrano troncati
  double res = 1;

  for (int i = 1; i <= a; i++) {
    res = res * i;
  }
  return res;
}

double factorial_big(int a) {
  // valori non interi verrano troncati
  double res = 0;

  for (int i = 1; i <= a; i++) {
    res += log10(i);
  }
  return pow(10, res);
}

=======
>>>>>>> 720b9df4d943c1e9538749956131d53c544c2ddb
int main() // Function Header
{
  unsigned int a = 0;
  cout << "Dammi un numero intero, calcolerò il suo fattoriale!\n";
  cin >> a;
  unsigned int result = factorial(a);
<<<<<<< HEAD
  double result2 = factorial_for(a);
  cout << "Fattoriale di " << a << " usando ricorsione = " << result << endl;
  cout << "Fattoriale di " << a << " usando un ciclo for = " << result2 << endl;

  cout << "\nDammi un numero intero grande, calcolerò il suo fattoriale "
          "approssimato!\n";
  int b = 0;
  cin >> b;
  cout << factorial_big(b) << endl;
=======
  cout << "Fattoriale di " << a << " = " << result << endl;
>>>>>>> 720b9df4d943c1e9538749956131d53c544c2ddb
  return 0;
}
