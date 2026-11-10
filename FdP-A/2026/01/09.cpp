/*
 * Spostamento circolare di un array
 *
 * Leggi il numero di elementi n (1..100), poi n interi e un intero k
 * (0 <= k < n). Stampa gli stessi valori spostati di k posizioni verso
 * l'inizio dell'array: il primo valore stampato e' quello che nell'array
 * originale occupa la posizione k, e i k valori iniziali finiscono in fondo,
 * nello stesso ordine in cui erano.
 * Per esempio con k = 2 i primi due valori passano in fondo:
 *   1 2 3 4 5  diventa  3 4 5 1 2
 *
 *   k=3: 1 2 3 4 5 -> 4 5 1 2 3
 *
 * Esempio di esecuzione:
 *   Number of elements: 5
 *   data[0] = 1
 *   data[1] = 2
 *   data[2] = 3
 *   data[3] = 4
 *   data[4] = 5
 *   k = 2
 *   Rotated: 3 4 5 1 2
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  // [0] [1] [2] [3] [4]
  // 1   2   3   4   5

  int arr[] = {1, 2, 3, 4, 5};
  int k = 2;
  int n = 5;

  // [2] [3] [4] [0] [1]
  // 3   4   5   1   2
  // x   x   x   _   _
  int res[] = {0, 0, 0, 0, 0};
  for (int i = 0; i < n - k; ++i) {
    res[i] = arr[k + i];
  }
  for (int i = k + 1; i < n; ++i) {
    // (k+1) - k -1 = k -k + 1 -1 = 0
    res[i] = arr[i - k - 1];
  }

  for (int i = 0; i < n; ++i) {
    cout << res[i] << " ";
  }
  cout << endl;

  return 0;
}
