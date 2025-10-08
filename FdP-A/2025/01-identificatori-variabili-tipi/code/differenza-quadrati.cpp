#include <iostream>
using namespace std;

int main() {
    int a, b;

    cout << "Inserire il primo intero: ";
    cin >> a;

    cout << "Inserire il secondo intero: ";
    cin >> b;

    int differenza = (a * a) - (b * b);

    cout << "La diﬀerenza tra i quadrati dei due numeri e': " <<
        differenza
        << endl;

    return 0;
}