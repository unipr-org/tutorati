#include <iostream>
using namespace std;

int main(){
    int dim;
    do {
        cout << "Inserire la dimensione dell'array: ";
        cin >> dim;
    } while(dim < 1);

    int array[dim];

    for(int i = 0; i < dim; i++) {
        cout << "Inserisci il " << i + 1 << " elemento: ";
        cin >> array[i];
    }

    int sommapari = 0;
    int sommadispari = 0;
    for(int i = 0; i < dim; i++){
        if(array[i] % 2 == 0){
            sommapari += array[i];
        } else {
            sommadispari += array[i];
        }
    }

    cout << "Somma pari: " << sommapari << endl;
    cout << "Somma dispari: " << sommadispari << endl;
    cout << "La differenza tra pari e dispari e': " <<
        sommapari - sommadispari << endl;

    return 0;
}