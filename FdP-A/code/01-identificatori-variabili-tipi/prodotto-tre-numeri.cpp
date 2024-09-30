#include <iostream>
using namespace std;

int main() {
    int _x, _y, _z;

    cout << "Inserire il primo numero: ";
    cin >> _x;

    cout << "Inserire il secondo numero: ";
    cin >> _y;

    cout << "Inserire il terzo numero: ";
    cin >> _z;

    cout << "Il prodotto dei tre numeri e': " << 
        _x * _y * _z 
        << endl;

    return 0;
}