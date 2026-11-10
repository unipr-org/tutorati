/*
 * Disegno di una piramide
 *
 * Leggi un'altezza n e disegna una piramide di '*' centrata: la riga i-esima
 * (da 1 a n) ha n-i spazi seguiti da 2*i-1 asterischi.
 *
 * Esempio di esecuzione:
 *   Height: 5
 *       *
 *      ***
 *     *****
 *    *******
 *   *********
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int height = 0;

  cout << "Height: ";
  cin >> height;

  for (int i = 1; i <= height; ++i) {
    for (int j = 1; j <= height - i; ++j) {
      cout << " ";
    }
    for (int j = 1; j <= 2 * i - 1; ++j) {
      cout << "*";
    }
    cout << endl;
  }

  return 0;
}
