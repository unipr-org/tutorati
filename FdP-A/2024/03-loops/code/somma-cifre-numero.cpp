#include <iostream>
using namespace std;

int main() {
    int _valore, cifra, somma = 0;

    cout << "Inserire un numero intero positivo: ";
    cin >> _valore;

    while(_valore > 0) {
        cifra = _valore % 10;
        somma += cifra;
        _valore /= 10;
        
        cout << cifra << endl;
    }

    cout << "La somma delle cifre e': " << somma << endl;

    return 0;
}