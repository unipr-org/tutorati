#include <iostream>
using namespace std;

int main() {
    int _mese;

    cout << "Inserire il mese (intero): ";
    cin >> _mese;

    if(_mese <= 0 || _mese > 12) {
        cout << "[ERRORE] Mese <= 0 o mese > 12" << endl;
    } else if (_mese == 1) {
        cout << "Gennaio" << endl;
    } else if (_mese == 2) {
        cout << "Febbraio" << endl;
    } else if (_mese == 3) {
        cout << "Marzo" << endl;
    } else if (_mese == 4) {
        cout << "Aprile" << endl;
    } else if (_mese == 5) {
        cout << "Maggio" << endl;
    } else if (_mese == 6) {
        cout << "Giugno" << endl;
    } else if (_mese == 7) {
        cout << "Luglio" << endl;
    } else if (_mese == 8) {
        cout << "Agosto" << endl;
    } else if (_mese == 9) {
        cout << "Settembre" << endl;
    } else if (_mese == 10) {
        cout << "Ottobre" << endl;
    } else if (_mese == 11) {
        cout << "Novembre" << endl;
    } else if (_mese == 12) {
        cout << "Dicembre" << endl;
    }

    return 0;
}