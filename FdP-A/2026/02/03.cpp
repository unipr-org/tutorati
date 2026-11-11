/*
 * Numeri perfetti
 *
 * Leggi un intero n e stampa tutti i numeri perfetti da 1 a n. Un numero e'
 * perfetto quando e' uguale alla somma dei suoi divisori propri, cioe' dei
 * divisori positivi diversi dal numero stesso (per esempio 6 = 1 + 2 + 3).
 * Stampa anche quanti numeri perfetti hai trovato.
 *
 * Esempio di esecuzione:
 *   n = 1000
 *   6 28 496
 *   Number of perfect numbers: 3
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int n;
  int count = 0;
  bool first = true;

  cout << "n = ";
  cin >> n;

  for (int value = 1; value <= n; ++value) {
    int sum = 0;

    for (int divisor = 1; divisor <= value / 2; ++divisor) {
      if (value % divisor == 0) {
        sum += divisor;
      }
    }

    if (sum == value) {
      if (!first) {
        cout << " ";
      }
      cout << value;
      first = false;
      ++count;
    }
  }

  cout << endl;
  cout << "Number of perfect numbers: " << count << endl;

  return 0;
}
