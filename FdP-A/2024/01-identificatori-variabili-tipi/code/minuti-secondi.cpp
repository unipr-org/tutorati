#include <iostream>
using namespace std;

int main() {
    int _minuti;

    cout << "Inserire i minuti: ";
    cin >> _minuti;

    int _secondi = _minuti * 60;

    cout << "L'equivalente tempo in secondi e': " << 
        _secondi
        << endl;

    return 0;
}