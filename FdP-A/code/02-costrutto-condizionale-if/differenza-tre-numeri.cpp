#include <iostream>
using namespace std;

int main() {
    int _a, _b, _c;

    cout << "Inserisci il primo valore: ";
    cin >> _a;

    cout << "Inserisci il secondo valore: ";
    cin >> _b;

    cout << "Inserisci il terzo valore: ";
    cin >> _c;

    int _max = _a;
    int _min = _a;

    if(_b > _max)
        _max = _b;
    if(_c > _max)
        _max = _c;

    if(_b < _min)
        _min = _b;
    if(_c < _min)
        _min = _c;

    int _risultato = _max - _min;

    cout << "Risultato: " << _risultato << endl;

    return 0;
}