#include <iostream>
using namespace std;

int main() {
    int _valore;

    cout << "Inserire un numero: ";
    cin >> _valore;

    int _risultato = _valore * (2 + (_valore % 2));

    cout << "Il risultato e': " << 
        _risultato 
        << endl;

    return 0;
}