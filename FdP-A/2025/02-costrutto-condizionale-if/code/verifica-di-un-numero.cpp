#include <iostream>
using namespace std;

int main() {
    int numero;

    cout << "Inserire un numero: ";
    cin >> numero;

    if (numero > 0) {
        cout << "Numero positivo" << endl;
    } else if (numero < 0) {
        cout << "Numero negativo" << endl;
    } else {
        cout << "Il numero e' uguale a 0" << endl;
    }

    return 0;
}