/*
 * Verifica dei numeri primi
 *
 * Leggi un intero n e stampa tutti i numeri primi da 2 fino a n, contando
 * quanti sono. Usa un ciclo esterno sui candidati e un ciclo interno sui
 * possibili divisori.
 *
 * Esempio di esecuzione:
 *   n = 30
 *   2 3 5 7 11 13 17 19 23 29
 *   Number of primes: 10
 */

#include <iomanip>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  // Usiamo il crivello di Eratostene
  int n = 123;

  unsigned int n_col = 10;
  unsigned int n_row = n % 10 ? (n / 10) + 1 : (n / 10);
  int table[n_row][n_col];

  for (int idx = 0; idx < n_row * n_col; ++idx) {
    unsigned int target_row = idx / n_col;
    unsigned int target_col = idx % n_col;

    // cout << "[DEBUG] target_row: " << target_row
    //      << ", target_col: " << target_col << endl;

    table[target_row][target_col] = idx < n ? idx + 1 : 0;
  }
  table[0][0] = 0;

  // stampa di controllo
  for (int i = 0; i < n_row; ++i) {
    for (int j = 0; j < n_col; ++j) {
      cout << setw(4) << table[i][j] << " ";
    }
    cout << endl;
  }

  // sufficiente arrivare fino a n/2 incluso:
  // se idx = n/2 allora idx*factor > n non appena factor>2.
  for (int idx = 1; idx <= n / 2; ++idx) {

    unsigned elem = idx + 1;
    // cout << "[DEBUG] elem: " << elem << endl;

    for (unsigned factor = 2; (elem * factor) <= n && factor <= (n / 2);
         ++factor) {
      // cout << "[DEBUG] factor: " << factor << endl;

      unsigned int target_row = ((elem * factor) - 1) / n_col;
      unsigned int target_col = ((elem * factor) - 1) % n_col;
      // cout << "[DEBUG] target_row: " << target_row << endl;
      // cout << "[DEBUG] target_col: " << target_col << endl;

      table[target_row][target_col] = 0;
    }
  }

  // stampa di controllo
  cout << endl;
  for (int i = 0; i < n_row; ++i) {
    for (int j = 0; j < n_col; ++j) {
      cout << setw(4) << table[i][j] << " ";
    }
    cout << endl;
  }

  unsigned int count = 0;

  cout << endl;
  for (int i = 0; i < n_row; ++i) {
    for (int j = 0; j < n_col; ++j) {
      if (table[i][j] > 0) {
        ++count;
        cout << setw(4) << table[i][j] << " ";
      }
    }
    cout << endl;
  }
  cout << "Number if primes: " << count << endl;
  return 0;
}
