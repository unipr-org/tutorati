/*
 * Cifre di un intero
 *
 * Leggi un intero positivo n. Senza usare stringhe, stampa le sue cifre in
 * ordine inverso, la somma delle cifre e indica se n e' palindromo, cioe' se
 * si legge allo stesso modo nei due versi.
 *
 * Esempio di esecuzione:
 *   n = 12321
 *   Reversed: 12321
 *   Sum of digits: 9
 *   12321 is a palindrome
 */

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

  int n = 12021;
  int n_copy = n;

  long reverse = 0;
  int sum = 0;
  int digit = 0;
  int exponent = 0;

  while (n_copy > 0) {
    digit = n_copy % 10;
    reverse = reverse * 10 + digit;
    sum += digit;

    n_copy /= 10;
    exponent += 1;
  }
  cout << "[INFO]" << " reverse: " << reverse << endl;
  cout << "[INFO]" << " sum: " << sum << endl;
  cout << "[INFO]" << " palindrome: " << (n == reverse ? "true" : "false")
       << endl;
  return 0;
}
