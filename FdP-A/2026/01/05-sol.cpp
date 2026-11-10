/*
 * Disegno di un triangolo
 *
 * Leggi un'altezza n e disegna un triangolo rettangolo di '*'.
 *
 * Esempio di esecuzione:
 *   Height: 5
 *   *
 *   **
 *   ***
 *   ****
 *   *****
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int height = 0;

  cout << "Height: ";
  cin >> height;

  for (int i = 1; i <= height; ++i) {
    for (int j = 1; j <= i; ++j) {
      cout << "*";
    }
    cout << endl;
  }

  return 0;
}
