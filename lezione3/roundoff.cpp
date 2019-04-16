/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 3

  Esempi di roundoff
*/

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
  double x=1e10;
  double f1=1/(sqrt(x*x+1)+x);
  double f2=1/(2*x);
  cout<<f1<<" "<<f2<<endl;
  return 0;
}
