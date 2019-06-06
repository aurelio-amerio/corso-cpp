/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 17

  elliptic

*/
#define PI 3.14159265358979
#define VERBOSE 1
// now I need a drink, alcoholic of course, after the
// heavy lectures involving quantum mechanics

#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

// righe = y
// colonne = x

void boundaryConditions(double **phi, double *x, double *y, int nx, int ny) {
  double dx = fabs(x[1] - x[0]);

  // condizioni su y
  for (int j = 0; j < nx; j++) {
    phi[0][j] = 0;
    phi[ny - 1][j] = 2.0 - x[j];
  }

  // a sinistra
  for (int i = 0; i < ny; i++) {
    phi[i][0] = phi[i][1]; //-dx*0
  }

  // a destra
  for (int i = 0; i < ny; i++) {
    phi[i][nx - 1] = phi[i][nx - 2] + dx * 3.;
  }

  return;
}

void SOR(double **solutions, double xmin, double xmax, double ymin, double ymax,
         int nx, int ny, double (*S)(double x, double y), double wsor,
         double tol) {

  double dx = (xmax - xmin) / (nx - 1);
  double dy = (ymax - ymin) / (ny - 1);


  double *x = new double[nx];
  double *y = new double[ny];

  int nmax = 1000;
  int niter = 0;

  // create phi0
  double **phi0 = new double *[ny];
  if (ny) {
    phi0[0] = new double[nx * ny];
    for (int i = 1; i < ny; ++i)
      phi0[i] = phi0[0] + i * nx;
  }

  // create phi1
  double **phi1 = new double *[ny];
  if (ny) {
    phi1[0] = new double[nx * ny];
    for (int i = 1; i < ny; ++i)
      phi1[i] = phi1[0] + i * nx;
  }

  // fill matrices with zeros
  for (int i = 0; i < ny; i++) {
    for (int j = 0; j < nx; j++) {
      phi0[i][j] = 0;
      phi1[i][j] = 0;
    }
  }

  // create x array
  for (int i = 0; i < nx; i++) {
    x[i] = xmin + dx * i;
  }

  // create y array
  for (int i = 0; i < ny; i++) {
    y[i] = ymin + dy * i;
  }

  // boundary conditions
  boundaryConditions(phi0, x, y, nx, ny);

  // paste phi0 into phi1
  for (int i = 0; i < ny; i++) {
    for (int j = 0; j < nx; j++)
      phi1[i][j] = phi0[i][j];
  }

  //start cycle
  while (niter < nmax) {
    // compute the phi1
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++)
        phi1[i][j] = (1 - wsor) * phi1[i][j] +
                     wsor * 0.25 *
                         (phi1[i + 1][j] + phi1[i - 1][j] + phi1[i][j + 1] +
                          phi1[i][j - 1] - dx * dy * S(x[i], y[j]));
    }

    // update boundary conditions
    boundaryConditions(phi1, x, y, nx, ny);

    // compute resudial
    double err = 0;
    for (int i = 1; i < ny-1; i++) {
      for (int j = 1; j < nx-1; j++)
        err += fabs(phi1[i][j] - phi0[i][j]) * dx * dy;
    }
    cout<<err<<endl;
    if (err < tol) {
      // paste phi1 into solution array
      for (int i = 1; i < ny - 1; i++) {
        for (int j = 1; j < nx - 1; j++)
          solutions[i][j] = phi1[i][j];
      }

      break;
    }
    // paste phi1 into phi0
    // paste phi1 into solution array
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++)
        phi0[i][j] = phi1[i][j];
    }
    niter++;
  }

#if VERBOSE
  cout << "n iter sor: " << niter << endl;
#endif

//paste solutions
for (int i = 0; i < ny; i++) {
  for (int j = 0; j < nx; j++)
    solutions[i][j] = phi1[i][j];
}

  // delete matrices
  if (ny) {
    delete[] phi0[0];
    delete[] phi1[0];
  }
  delete[] phi0;
  delete[] phi1;

  delete x;
  delete y;

  return;
}

double S(double x, double y) { return 0; }

int main() {

  double xmin = 0;
  double xmax = 2;
  double ymin = 0;
  double ymax = 1;

  double tol = 1e-7;

  int nx = 129;
  int ny = 65;

  double dx = (xmax - xmin) / (nx - 1);
  double dy = (ymax - ymin) / (ny - 1);

  double *x = new double[nx];
  double *y = new double[ny];

  // create x array
  for (int i = 0; i < nx; i++) {
    x[i] = xmin + dx * i;
  }

  // create y array
  for (int i = 0; i < ny; i++) {
    y[i] = ymin + dy * i;
  }

  // rows=y
  // columns=x

  // create solution matrix
  double **solutions = new double *[ny];
  if (ny) {
    solutions[0] = new double[nx * ny];
    for (int i = 1; i < ny; ++i)
      solutions[i] = solutions[0] + i * nx;
  }

  // fill zeros
  for (int i = 0; i < ny; i++) {
    for (int j = 0; j < nx; j++) {
      solutions[i][j] = 0;
    }
  }

  // sor
  double wsor = 2.0 / (1 + PI / nx);

  SOR(solutions, xmin, xmax, ymin, ymax, nx, ny, S, wsor, tol);

  ofstream file2;
  file2.open("sor_fluido.dat");

  for (int i = 0; i < ny; i++) {
    for (int j = 0; j < nx; j++) {
      file2 << x[j] << " " << y[i] << " " << solutions[i][j] << endl;
    }
  }
  file2.close();
  // end
  return 0;
}
