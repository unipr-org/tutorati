/*
 * Fusione di due array ordinati
 *
 * Leggi due dimensioni n e m (1..50), poi n interi in ordine crescente e m
 * interi in ordine crescente. Costruisci un terzo array che contiene tutti i
 * valori in ordine crescente, senza riordinare: sfrutta l'ordine dei due
 * array di partenza, confrontando ogni volta i due elementi correnti.
 *
 * Esempio di esecuzione:
 *   n = 4
 *   m = 3
 *   A: 1 4 9 12
 *   B: 2 3 10
 *   Merged: 1 2 3 4 9 10 12
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int n = 7;
  int m = 5;

  cout << "n = " << n << endl;
  cout << "m = " << m << endl;

  int a[n];
  int b[m];
  int merged[n + m];

  cout << "A: ";
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  cout << "B: ";
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }

  int i = 0;
  int j = 0;
  int k = 0;
  while (i < n && j < m) {
    if (a[i] <= b[j]) {
      merged[k] = a[i];
      ++i;
    } else {
      merged[k] = b[j];
      ++j;
    }
    ++k;
  }
  while (i < n) {
    merged[k] = a[i];
    ++i;
    ++k;
  }
  while (j < m) {
    merged[k] = b[j];
    ++j;
    ++k;
  }

  cout << "Merged:";
  for (int t = 0; t < k; ++t) {
    cout << " " << merged[t];
  }
  cout << endl;

  return 0;
}
