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

    for(int i = 2; _numero > 1; i++) {
        while(_numero % i == 0) {
            cout << i << " ";
            _numero /= i;
        }
    }
    
    cout << endl;

    return 0;
}