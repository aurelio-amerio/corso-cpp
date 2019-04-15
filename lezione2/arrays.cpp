/*
  Amerio Aurelio
  Algoritmi numerici per la fisica
  Lezione 2

  Arrays
*/

#include <iostream>
#include <math.h>   /* sqrt, pow */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
using namespace std;

double compute_average(double *array, int len);
double compute_variance(double *array, int len);
double compute_std_dev(double *array, int len);

int main() // Function Header
{
  // srand(time(NULL));
  srand48(time(NULL));
  int num_elem = 0;
  cout << "dammi il numero di elementi per un array riempito casualmente: ";
  cin >> num_elem;
  double *array_sample = new double[num_elem];
  for (int i = 0; i < num_elem; i++) {
    // array_sample[i] = rand() %1000;
    array_sample[i] = drand48();
  }
  cout << "average: " << compute_average(array_sample, num_elem) << endl;
  cout << "variance: " << compute_variance(array_sample, num_elem) << endl;
  cout << "std dev: " << compute_std_dev(array_sample, num_elem) << endl;

  // libera la memoria
  delete (array_sample);
  // termina il programma
  return 0;
}

double compute_average(double *array, int len) {
  double average = 0;
  double res = 0;
  for (int i = 0; i < len; i++) {
    res += array[i];
  }
  average = res / len;
  return average;
}

double compute_variance(double *array, int len) {
  double res = 0;
  double average = compute_average(array, len);
  double variance = 0;
  for (int i = 0; i < len; i++) {
    res += (array[i] - average)*(array[i] - average);
    // cout<<array[i]<<endl;
    // cout<<(array[i] - average)*(array[i] - average)<<endl;
  }
  variance = res / len;
  return variance;
}

double compute_std_dev(double *array, int len) {
  return sqrt(compute_variance(array, len));
}
