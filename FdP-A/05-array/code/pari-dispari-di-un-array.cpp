#include <iostream>
using namespace std;

int main(){
    int _dim;
    do {
        cout << "Inserire la dimensione dell'array: ";
        cin >> _dim;
    } while(_dim < 1);

    int array[_dim];

    for(int i = 0; i < _dim; i++) {
        cout << "Inserisci il " << i + 1 << " elemento: ";
        cin >> array[i];
    }

    int somma_pari = 0;
    int somma_dispari = 0;
    for(int i = 0; i < _dim; i++){
        if(array[i] % 2 == 0){
            somma_pari += array[i];
        } else {
            somma_dispari += array[i];
        }
    }

    cout << "Somma pari: " << somma_pari << endl;
    cout << "Somma dispari: " << somma_dispari << endl;
    cout << "La differenza tra pari e dispari e': " << 
        somma_pari - somma_dispari << endl;

    return 0;
}