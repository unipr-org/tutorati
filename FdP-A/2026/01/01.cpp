/*
 * Assegnazione della classe
 *
 * Scrivi un programma che legga un numero di matricola (intero positivo) e
 * assegni lo studente a una classe:
 *   - numero da 1 a 20                  -> Class A
 *   - numero 21 o superiore e pari      -> Class A
 *   - numero 21 o superiore e dispari   -> Class B
 *
 * Esempio di esecuzione:
 *   Enter student ID: 25
 *   Student 25 is in Class B
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int id = 0;

  do {
    cout << "Insert the id: ";

    cin >> id;

    if (id <= 0) {
      break;
    }
    // id > 0

    if (id >= 1 && id <= 20) {
      cout << "Class A" << endl;
      continue;
    }
    bool odd = id % 2;

    if (id % 2) {
      cout << "Class B" << endl;
    } else {
      cout << "Class A" << endl;
    }

  } while (true);

  return 0;
}
