#include "derivatives.h"
#include <fstream>

double func(double x);
double der_func(double x);

int main()
{
  ofstream forward;
  forward.open("forward.dat");
  ofstream backward;
  backward.open("backward.dat");
  ofstream centered;
  centered.open("central.dat");
  ofstream order_4;
  order_4.open("order_4.dat");

  double x0=1.;
  double h=0.;
  int n_points=30;
  double dh_log_inverse= 3. / n_points;
  for(int i=0; i<n_points;i++)
  {
    h=1./pow(10,i*dh_log_inverse);
    forward<<1./h<<" "<<fabs(forward_derivaive(func,x0,h)-der_func(x0))<<endl;
    backward<<1./h<<" "<<fabs(backward_derivaive(func,x0,h)-der_func(x0))<<endl;
    centered<<1./h<<" "<<fabs(central_derivaive(func,x0,h)-der_func(x0))<<endl;
    order_4<<1./h<<" "<<fabs(derivaive_f(func,x0,h)-der_func(x0))<<endl;
  }

  forward.close();
  backward.close();
  centered.close();
  order_4.close();
  return 0;
}

double func(double x)
{
  return sin(x);
}

double der_func(double x)
{
  return cos(x);
}
