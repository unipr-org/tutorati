#include <iostream>
using namespace std;

int main() {
    int _valore = 0;

    cout << "Inserire un valore intero positivo: ";
    cin >> _valore;

    int c = 0;
    int somma = 0;
    while(c <= _valore) {
        if(c % 2 == 0) {
            somma += c;
            cout << c << endl;
        }
        c++;
    }

    cout << "La somma e': " << somma << endl;

    return 0;
}