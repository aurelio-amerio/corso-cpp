// a library with helpful functions to solve ODEs

#include <fstream>
#include <math.h>

#define PRINT 0

using namespace std;

// prototype

void RKStep(double t, double *Y, void (*Ydot)(double, double *, double *),
            double dt, int neq);
void RK4Step(double t, double *Y, void (*Ydot)(double, double *, double *),
             double dt, int neq);
void EulerStep(double t, double *Y, void (*Ydot)(double, double *, double *),
               double dt, int neq);

void velocity_Verlet(double *X, double *V,
                     void (*acc)(double *X, double *res, int n_part), double h,
                     int n_part, int n_steps);

void verlet4(double *X, double *V,
             void (*acc)(double *X, double *res, int n_part), double h,
             int n_part, int n_steps);
