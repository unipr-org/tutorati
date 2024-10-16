#include <iostream>
using namespace std;

int main() {
    int _valore1, _valore2, mcm;

    cout << "Inserisci il primo valore: ";
    cin >> _valore1;
    cout << "Inserisci il secondo valore: ";
    cin >> _valore2;

    int max = 0;
    // max = (_valore1 > _valore2) ? _valore1 : _valore2;
    
    if(_valore1 > _valore2)
        max = _valore1;
    else 
        max = _valore2;

    while(true) {
        if(max % _valore1 == 0 && max % _valore2 == 0) {
            mcm = max;
            break;
        }
        max++;
    }

    cout << "L'mcm di " << _valore1 << " e " << _valore2 << " e': " << mcm << endl;

    return 0;
}