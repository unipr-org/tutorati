/*
 * Tavola pitagorica
 *
 * Stampa la tavola delle moltiplicazioni da 1 a 9, dalla riga 1 alla riga 9,
 * usando un for annidato. Usa un solo for per il ciclo esterno.
 *
 * Esempio di output:
 *   [1]  1  2  3  4  5  6  7  8  9
 *   [2]  2  4  6  8 10 12 14 16 18
 *   [3]  3  6  9 12 15 18 21 24 27
 *   ...
 *   [9]  9 18 27 36 45 54 63 72 81
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]) {
  for (int i = 1; i <= 9; ++i) {
    cout << "[" << i << "]";
    for (int j = 1; j <= 9; ++j) {
      cout << setw(3) << i * j;
    }
    cout << endl;
  }

  return 0;
}
