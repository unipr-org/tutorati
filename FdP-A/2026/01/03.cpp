/*
 * Pari/dispari e quoziente con resto
 *
 * Leggi due interi nelle variabili a e b. Stampa se ciascuno e' pari o
 * dispari, poi mostra quoziente e resto della divisione intera di a per b.
 * Se b vale 0 stampa un messaggio di errore al posto di quoziente e resto.
 *
 * Esempio di esecuzione:
 *   a = 17
 *   b = 5
 *   a is odd
 *   b is odd
 *   17 / 5 = quotient 3, remainder 2
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int a = 0;
  int b = 0;

  cout << "a = ";
  cin >> a;

  cout << "b = ";
  cin >> b;

  if (a % 2 == 0) {
    cout << "a is even" << endl;
  } else {
    cout << "a is odd" << endl;
  }

  if (b % 2 == 0) {
    cout << "b is even" << endl;
  } else {
    cout << "b is odd" << endl;
  }

  if (b == 0) {
    cout << "Cannot divide by zero" << endl;
  } else {
    cout << a << " / " << b << " = quotient " << a / b;
    cout << ", remainder " << a % b << endl;
  }

  return 0;
}
