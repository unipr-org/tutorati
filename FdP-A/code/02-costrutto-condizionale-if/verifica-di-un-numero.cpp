#include <iostream>
using namespace std;

int main() {
    int _numero;

    cout << "Inserire un numero: ";
    cin >> _numero;

    if (_numero > 0) {
        cout << "Numero positivo" << endl;
    } else if (_numero < 0) {
        cout << "Numero negativo" << endl;
    } else {
        cout << "Il numero e' uguale a 0" << endl;
    }

    return 0;
}