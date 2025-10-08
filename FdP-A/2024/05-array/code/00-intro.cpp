#include <iostream>
using namespace std;

int main(){
    int _dim;
    do{
        cout << "Dimensione array: ";
        cin >> _dim;
    } while (_dim < 1);

    int array[_dim];

    for(int i = 0; i < _dim; i++) {
        cout << "Inserire il " << i + 1 << " elemento: ";
        cin >> array[i];
    }

    for(int i = 0; i < _dim; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}