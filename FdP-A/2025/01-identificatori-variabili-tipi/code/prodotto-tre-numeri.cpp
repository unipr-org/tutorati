#include <iostream>
using namespace std;

int main() {
    int x, y, z;

    cout << "Inserire il primo numero: ";
    cin >> x;

    cout << "Inserire il secondo numero: ";
    cin >> y;

    cout << "Inserire il terzo numero: ";
    cin >> z;

    cout << "Il prodotto dei tre numeri e': " <<
        x * y * z
        << endl;

    return 0;
}