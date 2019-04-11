/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 1

  add one
*/

#include <iostream>
using namespace std;

void add_one(&int);

int main() {
  int a;
  return 0;
}

int add_one(int &a) {
  a++;
  return;
}
