/*
 * Minimo e massimo di un array con le posizioni
 *
 * Nell'array di 5 interi d = {88, 72, 95, 55, 63} trova il valore minimo e
 * il valore massimo, ciascuno con la sua posizione, e stampali.
 *
 * Output atteso:
 *   minimum is d[3]: 55
 *   maximum is d[2]: 95
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  int arr[] = {88, -1, 95, 55, 63};
  int min = arr[0];
  int max = arr[0];

  for (int i = 1; i < 5; ++i) {
    if (arr[i] > max) {
      max = arr[i];
    }
    if (arr[i] < min) {
      min = arr[i];
    }
  }

  cout << "Max: " << max << endl;
  cout << "Min: " << min << endl;

  return 0;
}
