#include <iostream>
using namespace std;

int main() {
    int _numero, _somma = 0;

    cout << "Inserire un numero intero positivo: ";
    cin >> _numero;

    while(_numero < 0){
        cout << "Valore errato!!" << endl;
        cout << "Inserire un numero intero positivo: ";
        cin >> _numero;
    }

    for(int i = 1; i < _numero; i++){
        if(_numero % i == 0) {
            _somma += i;
            cout << i << " ";
        }
    }

    cout << endl;

    if(_somma == _numero) {
        cout << "Il numero " << _numero << " e' perfetto" << endl;
    } else {
        cout << "Il numero " << _numero << " non e' perfetto" << endl;
    }

    return 0;
}