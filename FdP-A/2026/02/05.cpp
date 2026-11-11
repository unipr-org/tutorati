/*
 * Istogramma delle frequenze
 *
 * Leggi il numero di esami n (1..200), poi n voti interi da 0 a 30. Conta
 * quanti voti cadono in ciascuna fascia (0-5, 6-10, 11-15, 16-20, 21-25,
 * 26-30) e stampa un istogramma con un '*' per ogni voto della fascia.
 * Ignora i voti fuori dall'intervallo 0-30.
 *
 * Esempio di esecuzione:
 *   Number of exams: 8
 *   vote: 28
 *   vote: 12
 *   vote: 30
 *   vote: 7
 *   vote: 3
 *   vote: 25
 *   vote: 18
 *   vote: 9
 *    0- 5:  1 *
 *    6-10:  2 **
 *   11-15:  1 *
 *   16-20:  1 *
 *   21-25:  1 *
 *   26-30:  2 **
 */

#include <iomanip>
#include <iostream>
using namespace std;

struct Band {
  int low;
  int high;
  int count;
};

int main(int argc, char *argv[]) {
  const int band_count = 6;
  Band bands[band_count] = {{0, 5, 0},    {6, 10, 0},  {11, 15, 0},
                            {16, 20, 0},  {21, 25, 0}, {26, 30, 0}};

  int n;
  cout << "Number of exams: ";
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int vote;
    cout << "vote: ";
    cin >> vote;

    if (vote < 0 || vote > 30) {
      continue;
    }

    for (int b = 0; b < band_count; ++b) {
      if (vote >= bands[b].low && vote <= bands[b].high) {
        ++bands[b].count;
        break;
      }
    }
  }

  for (int b = 0; b < band_count; ++b) {
    cout << setw(4) << bands[b].low << "-" << setw(2) << bands[b].high << ":"
         << setw(3) << bands[b].count << " ";

    for (int star = 0; star < bands[b].count; ++star) {
      cout << "*";
    }

    cout << endl;
  }

  return 0;
}
