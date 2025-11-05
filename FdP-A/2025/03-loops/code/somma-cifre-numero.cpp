#include <iostream>
using namespace std;

int main() {
    int n, somma = 0;
    cout << "Inserisci un numero: ";
    cin >> n;

    int temp = n;
    while (temp > 0) {
        somma += temp % 10;
        temp /= 10;
    }
    cout << "Somma (while): " << somma << endl;

    temp = n;
    somma = 0;
    do {
        somma += temp % 10;
        temp /= 10;
    } while (temp > 0);
    cout << "Somma (do-while): " << somma << endl;

    return 0;
}
