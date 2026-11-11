/*
 * Ordinamento decrescente con insertion sort
 *
 * Leggi 5 interi da tastiera e stampali ordinati in modo decrescente usando
 * l'insertion sort: per ogni elemento, spostalo a sinistra finche' non trova
 * un elemento piu' grande, inserendolo nella posizione corretta.
 *
 * Esempio di esecuzione:
 *   Input 1: 5
 *   Input 2: 23
 *   Input 3: 11
 *   Input 4: 2
 *   Input 5: 17
 *   Descending: 23, 17, 11, 5, 2
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  const int size = 5;
  int data[size];

  for (int i = 0; i < size; ++i) {
    cout << "Input " << i + 1 << ": ";
    cin >> data[i];
  }

  for (int i = 1; i < size; ++i) {
    int current = data[i];
    int j = i - 1;

    while (j >= 0 && data[j] < current) {
      data[j + 1] = data[j];
      --j;
    }

    data[j + 1] = current;
  }

  cout << "Descending: ";
  for (int i = 0; i < size; ++i) {
    if (i > 0) {
      cout << ", ";
    }
    cout << data[i];
  }
  cout << endl;

  return 0;
}
