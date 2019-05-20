/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 10

  derivate
*/

#include <iostream>
#include <math.h>
using namespace std;

double forward_derivaive(double (*func)(double x), double x0, double h)
{

  double result=(func(x0+h)-func(x0))/h;

  return result;
}

double backward_derivaive(double (*func)(double x), double x0, double h)
{

  double result=(func(x0)-func(x0-h))/h;

  return result;
}

double central_derivaive(double (*func)(double x), double x0, double h)
{

  double result=(func(x0+h)-func(x0-h))/(2*h);

  return result;
}

double derivaive_f(double (*func)(double x), double x0, double h)
{

  double result=(func(x0-2*h)-8*func(x0-h)+8*func(x0+h)-func(x0+2*h))/(12*h);

  return result;
}
