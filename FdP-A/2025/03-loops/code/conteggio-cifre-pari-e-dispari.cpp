#include <iostream>
using namespace std;

int main() {
    int n, pari = 0, dispari = 0;
    cout << "Inserisci un numero: ";
    cin >> n;

    while (n > 0) {
        int cifra = n % 10;
        if (cifra % 2 == 0)
            pari++;
        else
            dispari++;
        n /= 10;
    }

    cout << "Cifre pari: " << pari << ", cifre dispari: " << dispari << endl;
    return 0;
}
