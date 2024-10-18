#include <iostream>
using namespace std;

int main() {
    int _valore = 0;
    cout << "Inserire un intero positivo: ";
    cin >> _valore;

    int i;
    int divisori = 0;
    for(i = 1; i <= _valore; i++){
        if(_valore % i == 0) {
            divisori++;
            cout << i << endl;
        }
    }

    cout << "Il numero " << _valore << 
            " ha " << divisori << " divisori." 
        << endl;

    return 0;
}