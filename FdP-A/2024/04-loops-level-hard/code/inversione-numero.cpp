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
    
    int _cifra;
    int _nuovoNumero = 0;
    
    while(_numero != 0) {
        _cifra = _numero % 10;
        
        _nuovoNumero = _nuovoNumero * 10 + _cifra;

        _numero /= 10;

        cout << _nuovoNumero << endl;
    }
    
    cout << "Il numero inverso e': " << _nuovoNumero << endl;
    
    return 0;
}
