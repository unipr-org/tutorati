#include <iostream>
using namespace std;

int main(){
    int _numero;

    cout << "Inserire un numero intero positivo: ";
    cin >> _numero;

    while(_numero < 0) {
        cout << "Errore" << endl;
        cout << "Inserire un numero intero positivo: ";
        cin >> _numero;
    }
    
    while(_numero >= 10) {
        int somma = 0;
        while(_numero > 0) {
            int cifra = _numero % 10;
            somma += cifra;
            _numero /= 10;
        }

        cout << somma << endl;
        _numero = somma;
    }
    
    cout << "La cifra singola e': " << _numero << endl;
    
    return 0;
}