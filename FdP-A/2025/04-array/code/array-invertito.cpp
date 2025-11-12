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

    for(int i = 0; i < dim; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    for(int i = 0; i < dim / 2; i++){
        int tmp = array[i];
        array[i] = array[dim - 1 - i];
        array[dim - 1 - i] = tmp;
    }

    for(int i = 0; i < dim; i++) {
        cout << array[i] << " ";
    }
    cout << endl;


    return 0;
}