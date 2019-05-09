/*
  Amerio Aurelio
  Algoritmi numerici per la fisica

  root finder prototype
*/
#define DEBUG 0

#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

double bisec(double (*)(double), double, double, double, double);

double false_pos(double (*)(double), double, double, double, double);

double secant(double (*)(double), double, double, double, double);

double newton(double (*)(double), double (*)(double), double, double, double,
              double);

void bracket(double (*)(double), double, double, int, double *, double *,
             int &);
