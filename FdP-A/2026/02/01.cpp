/*
 * Rimozione dei duplicati da un array
 *
 * Leggi il numero di elementi n (1..100), poi n interi. Elimina i valori
 * ripetuti tenendo solo la prima occorrenza di ciascuno e compattando i
 * valori rimasti nelle prime posizioni dell'array, senza usare un secondo
 * array. Stampa il nuovo numero di elementi e i valori rimasti, nello stesso
 * ordine in cui comparivano.
 *
 * Esempio di esecuzione:
 *   Number of elements: 8
 *   data[0] = 5
 *   data[1] = 3
 *   data[2] = 5
 *   data[3] = 7
 *   data[4] = 3
 *   data[5] = 5
 *   data[6] = 9
 *   data[7] = 7
 *   New size: 4
 *   Result: 5 3 7 9
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int data[] = {1, 2, 3, 4, 4, 2, 3, 1, 5, 9};
  int len = 10;

  int idx = 0;
  bool found = false;
  for (int i = 1; i < len; ++i) {
    found = false;
    for (int j = i - 1; j >= 0; --j) {
      if (data[i] == data[j]) {

        cout << "[DEBUG] found duplicate: " << data[i] << endl;
        found = true;
        break;
      }
    }

    if (found) {
      continue;
    }

    data[idx] = data[i];
    ++idx;
  }

  for (int i = 0; i < idx; ++i) {
    cout << data[i];
  }
  cout << endl;

  return 0;
}
