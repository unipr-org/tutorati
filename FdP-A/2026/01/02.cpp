/*
 * Massimo di tre interi
 *
 * Leggi tre interi distinti da tastiera, riscrivi i valori nell'ordine in cui
 * sono stati inseriti, poi stampa il maggiore.
 *
 * Esempio di esecuzione:
 *   a = 12
 *   b = 45
 *   c = 7
 *   Inputs: a=12, b=45, c=7
 *   Maximum is 45
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int a, b, c;

  a = b = c = 0;

  // a = 0;
  // b = 0;
  // c = 0;

  cout << "Inserire primo valore: ";
  cin >> a;

  bool ok = false;
  do {
    cout << "Inserire secondo valore: ";
    cin >> b;

    if (b != a) {
      ok = true;
    }
  } while (!ok);

  ok = false;
  do {
    cout << "Inserire terzo valore: ";
    cin >> c;

    if (c != a && c != b) {
      ok = true;
    }
  } while (!ok);

  int max = a;
  if (b > max) {
    max = b;
  }
  if (c > max) {
    max = c;
  }

  cout << a << " " << b << " " << c << endl;
  cout << "Massimo: " << max << endl;
}
