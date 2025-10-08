#include <iostream>
using namespace std;

int main() {
    int base, altezza;

    cout << "Inserire la base del rettangolo: ";
    cin >> base;

    cout << "Inserire l'altezza del rettangolo: ";
    cin >> altezza;

    int area = base * altezza;

    cout << "L'area del rettangolo e': " <<
        area
        << endl;

    return 0;
}