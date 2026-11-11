/*
 * Generatore pseudo-casuale congruenziale lineare
 *
 * Genera 100 numeri pseudo-casuali con la ricorrenza
 *   x(n+1) = (a * x(n) + b) mod m
 * con a = 717, b = 23, m = 65536 e valore iniziale x = 1234.
 *
 * Converti ogni valore in un numero reale y in [0, 1) con y = x / m.
 *
 * Stampa 10 valori per riga con 3 decimali, poi la media e la proporzione di
 * valori che cadono in [0.2, 0.4).
 *
 * Esempio di output (primi valori):
 *   0.501 0.211 0.636 0.298 0.626 0.530 0.119 0.238 0.782 0.955
 *   0.923 0.543 0.112 0.315 0.813 0.165 0.005 0.687 0.807 0.307
 *   ...
 *
 *   Average is 0.505
 *   Proportion of values in [0.2, 0.4) is 0.200
 */

#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  const int a = 717;
  const int b = 23;
  const int m = 65536;
  const int count = 100;

  int x = 1234;
  double sum = 0.0;
  int in_range = 0;

  // https://cplusplus.com/reference/ios/fixed/
  // https://cplusplus.com/reference/iomanip/setprecision/
  cout << fixed << setprecision(3);
  for (int i = 0; i < count; ++i) {
    x = (a * x + b) % m;
    double y = (double)(x) / m;
    sum += y;
    if (y >= 0.2 && y < 0.4) {
      ++in_range;
    }

    if (i % 10 != 0) {
      cout << " ";
    }
    cout << y;
    if (i % 10 == 9) {
      cout << endl;
    }
  }

  cout << endl;
  cout << "Average is " << sum / count << endl;
  cout << "Proportion of values in [0.2, 0.4) is " << (double)(in_range) / count
       << endl;

  return 0;
}
