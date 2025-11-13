#include <iostream>
using namespace std;

int main(){
    int dim;
    do{
        cout << "Dimensione array: ";
        cin >> dim;
    } while (dim < 1);

    int array[dim];

    for(int i = 0; i < dim; i++) {
        cout << "Inserire il " << i + 1 << " elemento: ";
        cin >> array[i];
    }

    for(int i = 0; i < dim; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    return 0;
}