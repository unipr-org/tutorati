/*
 * Statistiche di un array
 *
 * Leggi il numero di elementi n (1..100), poi n interi. Stampa minimo,
 * massimo, somma, media e quanti valori sono strettamente maggiori della
 * media.
 *
 * Esempio di esecuzione:
 *   Number of elements: 5
 *   data[0] = 10
 *   data[1] = 20
 *   data[2] = 30
 *   data[3] = 15
 *   data[4] = 25
 *   Min: 10
 *   Max: 30
 *   Sum: 100
 *   Average: 20.0
 *   Above average: 2
 */

#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int data[100] = {0};
  int n = 0;

  cout << "Number of elements: ";
  cin >> n;

  for (int i = 0; i < n; ++i) {
    cout << "data[" << i << "] = ";
    cin >> data[i];
  }

  int min_value = data[0];
  int max_value = data[0];
  int sum = 0;

  for (int i = 0; i < n; ++i) {
    if (data[i] < min_value) {
      min_value = data[i];
    }
    if (data[i] > max_value) {
      max_value = data[i];
    }
    sum += data[i];
  }

  double average = (double)(sum) / n;

  int above_average = 0;
  for (int i = 0; i < n; ++i) {
    if (data[i] > average) {
      ++above_average;
    }
  }

  cout << "Min: " << min_value << endl;
  cout << "Max: " << max_value << endl;
  cout << "Sum: " << sum << endl;
  cout << "Average: " << fixed << setprecision(2) << average << endl;
  cout << "Above average: " << above_average << endl;

  return 0;
}
