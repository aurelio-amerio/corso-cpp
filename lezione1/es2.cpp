#include <iostream>
using namespace std;

int main() {
  cout << "using for loop" << endl;

  for (int i = 1; i <= 10; i++) {
    if (i % 2 != 0) {
      cout << i << endl;
    }
  }

  cout << "using while loop" << endl;

  int i = 1;
  while (i < 11) {
    if (i % 2 != 0) {
      cout << i << endl;
    }
    i++;
  }
  return 0;
}
