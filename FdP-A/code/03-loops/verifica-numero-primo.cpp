#include <iostream>
using namespace std;

int main() {
    int _valore = 0;
    cout << "Inserire un intero positivo: ";
    cin >> _valore;

    int i;
    bool _primo = true;

    for(i = 2; i < _valore; i++){
        if(_valore % i == 0) {
            _primo = false;
        }
    }

    if(_primo) {
        cout << _valore << " e' primo." << endl;
    } else {
        cout << _valore << " non e' primo." << endl;
    }

    return 0;
}