#include <iostream>
using namespace std;

int main() {
    int valore;

    cout << "Inserire un numero: ";
    cin >> valore;

    int risultato = valore * (2 + (valore % 2));

    cout << "Il risultato e': " <<
        risultato
        << endl;

    return 0;
}