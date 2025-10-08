#include <iostream>
using namespace std;

int main() {
    int _base, _altezza;

    cout << "Inserire la base del rettangolo: ";
    cin >> _base;

    cout << "Inserire l'altezza del rettangolo: ";
    cin >> _altezza;

    int _area = _base * _altezza;

    cout << "L'area del rettangolo e': " << 
        _area
        << endl;

    return 0;
}