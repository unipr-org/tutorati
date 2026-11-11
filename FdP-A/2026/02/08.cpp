/*
 * Matrice trasposta e somme di riga e colonna
 *
 * Leggi le dimensioni r e c (1..10), poi gli r*c interi della matrice.
 * Stampa la matrice una riga per volta, poi la somma di ogni riga, la somma
 * di ogni colonna e la matrice trasposta, cioe' quella che ha le righe
 * scambiate con le colonne: l'elemento (i, j) della trasposta e' l'elemento
 * (j, i) della matrice originale.
 * Usa due cicli annidati per leggere la matrice e due cicli annidati per
 * stampare la trasposta.
 *
 * Esempio di esecuzione:
 *   Rows: 2
 *   Cols: 3
 *   data[0][0] = 1
 *   data[0][1] = 2
 *   data[0][2] = 3
 *   data[1][0] = 4
 *   data[1][1] = 5
 *   data[1][2] = 6
 *   Matrix:
 *   1 2 3
 *   4 5 6
 *   Row sums: 6 15
 *   Column sums: 5 7 9
 *   Transpose:
 *   1 4
 *   2 5
 *   3 6
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  const int max_size = 10;
  int rows = 0;
  int cols = 0;
  int data[max_size][max_size];

  cout << "Rows: ";
  cin >> rows;
  cout << "Cols: ";
  cin >> cols;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      cout << "data[" << i << "][" << j << "] = ";
      cin >> data[i][j];
    }
  }

  cout << "Matrix:" << endl;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j > 0) {
        cout << " ";
      }
      cout << data[i][j];
    }
    cout << endl;
  }

  cout << "Row sums:";
  for (int i = 0; i < rows; ++i) {
    int sum = 0;
    for (int j = 0; j < cols; ++j) {
      sum += data[i][j];
    }
    cout << " " << sum;
  }
  cout << endl;

  cout << "Column sums:";
  for (int j = 0; j < cols; ++j) {
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
      sum += data[i][j];
    }
    cout << " " << sum;
  }
  cout << endl;

  cout << "Transpose:" << endl;
  for (int i = 0; i < cols; ++i) {
    for (int j = 0; j < rows; ++j) {
      if (j > 0) {
        cout << " ";
      }
      cout << data[j][i];
    }
    cout << endl;
  }

  return 0;
}
