#include <iostream>
using namespace std;

int main(){
    int _dim, x;
    do {
        cout << "Inserire la dimensione dell'array: ";
        cin >> _dim;
    } while(_dim < 1);

    int array[_dim];

    for(int i = 0; i < _dim; i++) {
        cout << "Inserisci il " << i + 1 << " elemento: ";
        cin >> array[i];
    }

    cout << "Inserisci un numero x: ";
    cin >> x;

    int counter = 0;

    for(int i = 0; i < _dim; i++) {
        if(array[i] % x == 0) {
            counter++;
            cout << array[i] << " multiplo di " << x << endl;
        }
    }

    if(counter == 0){
        cout << "Non ci sono multipli" << endl;
    } else {
        cout << "Il numero di multipli e' " << counter << endl;
    }

    return 0;
}