#include <iostream>
using namespace std;

int main() {
    int minuti;

    cout << "Inserire i minuti: ";
    cin >> minuti;

    int secondi = minuti * 60;

    cout << "L'equivalente tempo in secondi e': " <<
        secondi
        << endl;

    return 0;
}