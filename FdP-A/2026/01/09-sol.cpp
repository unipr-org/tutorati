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
  int data[] = {1, 2, 3, 4, 5};
  int len = 5;
  int k = 3;

  /*
   * 0 1 2 3 4 ---> 2 3 4 0 1
   * 3 4 0 1 2
   * _ _ + + +
   *
   * -> se '_' vale (5-k+curr), dove '_' equiv (curr<k)
   * -> se '+' vale (curr-k), dove '+' equiv (curr >= k)
   * */

  int curr = 0;
  int curr_elem = data[curr];
  int dest = 0;
  int dest_elem = 0;

  for (int i = 0; i < len; ++i) {
    cout << data[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < len; ++i) {
    if (curr < k)
      dest = len - k + curr;
    else
      dest = curr - k;

    cout << "[DEBUG] curr: " << curr << ", ";
    // backup destination elem
    dest_elem = data[dest];
    // current elem placing
    data[dest] = curr_elem;
    // new curr to be considered
    curr = dest;
    // new elem to be placed
    curr_elem = dest_elem;

    cout << "[DEBUG] dest: " << dest << ", dest_elem: " << dest_elem
         << ", data: ";
    for (int i = 0; i < len; ++i) {
      cout << data[i] << " ";
    }
    cout << endl;
  }

  for (int i = 0; i < len; ++i) {
    cout << data[i] << " ";
  }
  cout << endl;

  return 0;
}
