/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 6

  random guess
*/

#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

int main() // Function Header
{
  srand(time(NULL));
  int secret = rand() % 100 + 1;
  int min = 0;
  int max = 100;
  int n_guess = 0;
  int guess;

  while (1) {
    cout << "[" << min << "," << max << "]"
         << " prova: ";
    cin >> guess;
    if (guess == secret) {
      n_guess++;
      cout << "complimenti!" << endl;
      break;
    } else if (guess > max || guess < min) {
      cout << "il numero deve essere compreso tra " << min << " e " << max
           << "!" << endl;
    } else {
      if (guess > secret) {
        max = guess;
        n_guess++;
      } else {
        min = guess;
        n_guess++;
      }
    }
  }
  cout << "ci hai messo " << n_guess << " tentativi!"<<endl;
  return 0;
}
// now I need a drink, alcoholic of course
// 3.1415926
