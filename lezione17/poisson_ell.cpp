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

void jacobi(double **solutions, double xmin, double xmax, double ymin,
            double ymax, int nx, int ny, double (*S)(double x, double y),
            double tol) {

  double dx = (xmax - xmin) / (nx - 1);
  double dy = (ymax - ymin) / (ny - 1);

  double *x = new double[nx];
  double *y = new double[ny];

  int nmax = 50000;
  int niter = 0;

  // create phi0
  double **phi0 = new double *[ny];
  if (ny) {
    phi0[0] = new double[nx * ny];
    for (int i = 1; i < ny; ++i)
      phi0[i] = phi0[0] + i * nx;
  }

  // paste boundary conditions into phi0
  for (int i = 0; i < ny; i++) {
    for (int j = 0; j < nx; j++)
      phi0[i][j] = solutions[i][j];
  }

  // create phi1
  double **phi1 = new double *[ny];
  if (ny) {
    phi1[0] = new double[nx * ny];
    for (int i = 1; i < ny; ++i)
      phi1[i] = phi1[0] + i * nx;
  }

  // create x array
  for (int i = 0; i < nx; i++) {
    x[i] = xmin + dx * i;
  }

  // create y array
  for (int i = 0; i < ny; i++) {
    y[i] = ymin + dy * i;
  }

  while (niter < nmax) {
    // compute the phi1
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++)
        phi1[i][j] = 0.25 * (phi0[i + 1][j] + phi0[i - 1][j] + phi0[i][j + 1] +
                             phi0[i][j - 1] - dx * dy * S(x[i], y[j]));
    }

    // update phi0
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++)
        phi0[i][j] = phi1[i][j];
    }

    // compute resudial
    double err = 0;
    double deltax2, deltay2;
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++) {
        deltax2 = phi0[i + 1][j] - 2.0 * phi0[i][j] + phi0[i - 1][j];
        deltay2 = phi0[i][j + 1] - 2.0 * phi0[i][j] + phi0[i][j - 1];
        err += fabs(deltax2 + deltay2 - dx * dy * S(x[i], y[j]));
      }
    }
    if (err < tol) {
      // paste phi0 into solution array
      for (int i = 1; i < ny - 1; i++) {
        for (int j = 1; j < nx - 1; j++)
          solutions[i][j] = phi0[i][j];
      }

      break;
    }
    niter++;
  }
#if VERBOSE
  cout << "n iter jacobi: " << niter << endl;
#endif

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

void gauss_seidel(double **solutions, double xmin, double xmax, double ymin,
                  double ymax, int nx, int ny, double (*S)(double x, double y),
                  double tol) {

  double dx = (xmax - xmin) / (nx - 1);
  double dy = (ymax - ymin) / (ny - 1);

  double *x = new double[nx];
  double *y = new double[ny];

  int nmax = 50000;
  int niter = 0;

  // create phi0
  double **phi0 = new double *[ny];
  if (ny) {
    phi0[0] = new double[nx * ny];
    for (int i = 1; i < ny; ++i)
      phi0[i] = phi0[0] + i * nx;
  }

  // paste boundary conditions into phi0
  for (int i = 0; i < ny; i++) {
    for (int j = 0; j < nx; j++)
      phi0[i][j] = solutions[i][j];
  }

  // create x array
  for (int i = 0; i < nx; i++) {
    x[i] = xmin + dx * i;
  }

  // create y array
  for (int i = 0; i < ny; i++) {
    y[i] = ymin + dy * i;
  }

  while (niter < nmax) {
    // compute the phi1
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++)
        phi0[i][j] = 0.25 * (phi0[i + 1][j] + phi0[i - 1][j] + phi0[i][j + 1] +
                             phi0[i][j - 1] - dx * dy * S(x[i], y[j]));
    }

    // compute resudial
    double err = 0;
    double deltax2, deltay2;
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++) {
        deltax2 = phi0[i + 1][j] - 2.0 * phi0[i][j] + phi0[i - 1][j];
        deltay2 = phi0[i][j + 1] - 2.0 * phi0[i][j] + phi0[i][j - 1];
        err += fabs(deltax2 + deltay2 - dx * dy * S(x[i], y[j]));
      }
    }
    if (err < tol) {
      // paste phi0 into solution array
      for (int i = 1; i < ny - 1; i++) {
        for (int j = 1; j < nx - 1; j++)
          solutions[i][j] = phi0[i][j];
      }

      break;
    }
    niter++;
  }
#if VERBOSE
  cout << "n iter g-s: " << niter << endl;
#endif

  // delete matrices
  if (ny) {
    delete[] phi0[0];
  }
  delete[] phi0;

  delete x;
  delete y;

  return;
}

void SOR(double **solutions, double xmin, double xmax, double ymin, double ymax,
         int nx, int ny, double (*S)(double x, double y), double wsor,
         double tol) {

  double dx = (xmax - xmin) / (nx - 1);
  double dy = (ymax - ymin) / (ny - 1);

  double *x = new double[nx];
  double *y = new double[ny];

  int nmax = 50000;
  int niter = 0;

  // create phi0
  double **phi0 = new double *[ny];
  if (ny) {
    phi0[0] = new double[nx * ny];
    for (int i = 1; i < ny; ++i)
      phi0[i] = phi0[0] + i * nx;
  }

  // paste boundary conditions into phi0
  for (int i = 0; i < ny; i++) {
    for (int j = 0; j < nx; j++)
      phi0[i][j] = solutions[i][j];
  }

  // create x array
  for (int i = 0; i < nx; i++) {
    x[i] = xmin + dx * i;
  }

  // create y array
  for (int i = 0; i < ny; i++) {
    y[i] = ymin + dy * i;
  }

  while (niter < nmax) {
    // compute the phi1
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++)
        phi0[i][j] = (1 - wsor) * phi0[i][j] +
                     wsor * 0.25 *
                         (phi0[i + 1][j] + phi0[i - 1][j] + phi0[i][j + 1] +
                          phi0[i][j - 1] - dx * dy * S(x[i], y[j]));
    }

    // compute resudial
    double err = 0;
    double deltax2, deltay2;
    for (int i = 1; i < ny - 1; i++) {
      for (int j = 1; j < nx - 1; j++) {
        deltax2 = phi0[i + 1][j] - 2.0 * phi0[i][j] + phi0[i - 1][j];
        deltay2 = phi0[i][j + 1] - 2.0 * phi0[i][j] + phi0[i][j - 1];
        err += fabs(deltax2 + deltay2 - dx * dy * S(x[i], y[j]));
      }
    }
    if (err < tol) {
      // paste phi0 into solution array
      for (int i = 1; i < ny - 1; i++) {
        for (int j = 1; j < nx - 1; j++)
          solutions[i][j] = phi0[i][j];
      }

      break;
    }
    niter++;
  }
#if VERBOSE
  cout << "n iter sor: " << niter << endl;
#endif

  // delete matrices
  if (ny) {
    delete[] phi0[0];
  }
  delete[] phi0;

  delete x;
  delete y;

  return;
}

double S(double x, double y) {
  const static double rho0 = 1;
  const static double a = 0.1;
  double r = sqrt(x * x + y * y);
  double sol;

  if (r <= a)
    sol = rho0;
  else
    sol = 0;

  return 0;
}

double sol_func(double x, double y) {
  double a = 0.1;
  double rho0 = 1;

  double r = sqrt(x * x + y * y);

  if (r <= a)
    return -rho0 * r * r / 4.0;
  else
    return -rho0 * a * a * 0.5 * (log(r / a) + 0.5);
}

int main() {

  double xmin = -1;
  double xmax = 1;
  double ymin = -1;
  double ymax = 1;

  double tol = 1e-5;

  int n = 101;

  double dx = (xmax - xmin) / (n - 1);
  double dy = (ymax - ymin) / (n - 1);

  double *x = new double[n];
  double *y = new double[n];

  // create x array
  for (int i = 0; i < n; i++) {
    x[i] = xmin + dx * i;
  }

  // create y array
  for (int i = 0; i < n; i++) {
    y[i] = ymin + dy * i;
  }
  ofstream file_sol;
  file_sol.open("sol_p.dat");
  // create solution matrix
  double **solutions = new double *[n];
  if (n) {
    solutions[0] = new double[n * n];
    for (int i = 1; i < n; ++i)
      solutions[i] = solutions[0] + i * n;
  }

  // fill solution matrix the lazy way
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      solutions[i][j] = sol_func(x[i], y[i]);
      file_sol << x[i] << " " << y[j] << " " << solutions[i][j] << endl;
    }
  }
  // fill zeros
  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < n - 1; j++) {
      solutions[i][j] = 0;
    }
  }

  jacobi(solutions, xmin, xmax, ymin, ymax, n, n, S, tol);

  ofstream file;
  file.open("jacobi_p.dat");

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      file << x[i] << " " << y[j] << " " << solutions[i][j] << endl;
    }
  }
  file.close();

  // gauss

  // fill zeros
  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < n - 1; j++) {
      solutions[i][j] = 0;
    }
  }

  gauss_seidel(solutions, xmin, xmax, ymin, ymax, n, n, S, tol);

  ofstream file1;
  file1.open("gauss_seidel_p.dat");

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      file1 << x[i] << " " << y[j] << " " << solutions[i][j] << endl;
    }
  }
  file1.close();

  // sor
  double wsor = 2.0 / (1 + PI / n);
  // fill zeros
  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < n - 1; j++) {
      solutions[i][j] = 0;
    }
  }

  SOR(solutions, xmin, xmax, ymin, ymax, n, n, S, wsor, tol);

  ofstream file2;
  file2.open("sor_p.dat");

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      file2 << x[i] << " " << y[j] << " " << solutions[i][j] << endl;
    }
  }
  file2.close();
  file_sol.close();
  // end
  return 0;
}
