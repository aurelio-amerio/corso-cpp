#include <iostream>
using namespace std;
int main() {
  cout << "using for loop" << endl;

  for (int i = 1; i <= 10; i++) {
    cout << i << endl;
  }

  cout << "using while loop" << endl;

  int j = 1;

  while (j < 11) {
    cout << j << endl;
    j++;
  }
  return 0;
}
