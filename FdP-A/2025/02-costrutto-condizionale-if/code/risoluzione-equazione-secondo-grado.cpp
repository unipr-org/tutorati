#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int a, b, c;

    cout << "Inserire il valore di a: ";
    cin >> a;
    cout << "Inserire il valore di b: ";
    cin >> b;
    cout << "Inserire il valore di c: ";
    cin >> c;

    if (a != 0) {
        int delta = b * b - 4 * a * c;

        if (delta > 0) {
            float x1 = ((-1) * b + sqrt(delta)) / (2 * a);
            float x2 = ((-1) * b - sqrt(delta)) / (2 * a);

            cout << "Le due soluzioni sono x1 = " << x1 << " e x2 = " << x2 << endl;
        } else if (delta == 0) {
            float x = ((-1) * b) / (2 * a);
            cout << "La soluzione e' x = " << x << endl;
        } else {
            cout << "Delta negativo" << endl;
        }
    } else
        cout << "Non è una equazione di secondo grado" << endl;

    return 0;
}