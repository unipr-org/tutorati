#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int _a, _b, _c;

    cout << "Inserire il valore di a: ";
    cin >> _a;
    cout << "Inserire il valore di b: ";
    cin >> _b;
    cout << "Inserire il valore di c: ";
    cin >> _c;

    int _delta = _b * _b - 4 * _a * _c;

    if (_delta > 0) {
        float _x1 = ((-1) * _b + sqrt(_delta)) / (2 * _a);
        float _x2 = ((-1) * _b - sqrt(_delta)) / (2 * _a);

        cout << "Le due soluzioni sono x1 = " << _x1 << " e x2 = " << _x2 << endl;
    } else if (_delta == 0) {
        float x = ((-1) * _b) / (2 * _a);
        cout << "La soluzione e' x = " << x << endl;
    } else {
        cout << "Delta negativo" << endl;
    }

    return 0;
}