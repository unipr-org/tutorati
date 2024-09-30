#include <iostream>
using namespace std;

int main() {
    int _minuti;

    cout << "Inserire i minuti: ";
    cin >> _minuti;

    cout << "L'equivalente tempo in secondi e': " << 
        _minuti * 60 
        << endl;

    return 0;
}