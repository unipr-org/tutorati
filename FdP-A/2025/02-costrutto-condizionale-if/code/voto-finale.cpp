#include <iostream>
using namespace std;

int main(){
    int voto;

    cout << "Inserire il voto: ";
    cin >> voto;

    if(voto < 0 || voto > 100) {
        cout << "Errore" << endl;
    } else if(voto < 60) {
        cout << "Insufficiente" << endl;
    } else if (voto < 70) {
        cout << "Sufficiente" << endl;
    } else if (voto < 80) {
        cout << "Buono" << endl;
    } else if (voto < 90) {
        cout << "Ottimo" << endl;
    } else {
        cout << "Eccellente" << endl;
    }

    return 0;
}