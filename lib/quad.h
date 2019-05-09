/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 4

  quadratura numerica
*/
#include <iomanip>
#include <iostream>
#include <math.h>

#define DEBUG 0

using namespace std;

// prototypes

double rect_quad(double (*func)(double x), double a, double b, int n);

double mid_quad(double (*func)(double x), double a, double b, int n);

double trapz(double (*func)(double x), double a, double b, int n);

double simps(double (*func)(double x), double a, double b, int n);

double simps(double (*func)(double x), double a, double b, double tol);

double gauss_order(double (*func)(double x), double a, double b, int order);

double gauss(double (*func)(double x), double a, double b, int n_points, int order);

double gauss(double (*func)(double x), double a, double b, double tol);
