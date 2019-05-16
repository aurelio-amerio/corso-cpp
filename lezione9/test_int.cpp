#include "../lib/quad.h"

double func(double x) { return x * x * x + 3; }

int main() {
  double res = gauss(func, 1., 3., 10, 5);
  cout<<res<<endl;
  return 0;
}
