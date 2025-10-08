#include <iostream>
using namespace std;

int main(){
    int _voto;

    cout << "Inserire il voto: ";
    cin >> _voto;

    if(_voto < 0 || _voto > 100) {
        cout << "Errore" << endl;
    } else if(_voto < 60) {
        cout << "Insufficiente" << endl;
    } else if (_voto < 70) {
        cout << "Sufficiente" << endl;
    } else if (_voto < 80) {
        cout << "Buono" << endl;
    } else if (_voto < 90) {
        cout << "Ottimo" << endl;
    } else {
        cout << "Eccellente" << endl;
    }

    return 0;
}