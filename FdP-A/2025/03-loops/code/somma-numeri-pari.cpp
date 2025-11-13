#include <iostream>
using namespace std;

int main() {
    int n, i = 0, somma = 0;
    cout << "Inserisci un numero: ";
    cin >> n;

    while (i <= n) {
        if (i % 2 == 0)
            somma += i;
        i++;
    }
    cout << "Somma (while): " << somma << endl;

    i = 0;
    somma = 0;
    do {
        if (i % 2 == 0)
            somma += i;
        i++;
    } while (i <= n);
    cout << "Somma (do-while): " << somma << endl;

    return 0;
}
