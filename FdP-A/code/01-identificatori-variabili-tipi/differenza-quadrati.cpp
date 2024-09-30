#include <iostream>
using namespace std;

int main() {
    int _a, _b;

    cout << "Inserire il primo intero: ";
    cin >> _a;

    cout << "Inserire il secondo intero: ";
    cin >> _b;

    cout << "La diﬀerenza tra i quadrati dei due numeri e': " << 
        (_a * _a) - (_b * _b)
        << endl;

    return 0;
}