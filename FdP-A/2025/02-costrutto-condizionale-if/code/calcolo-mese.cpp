#include <iostream>
using namespace std;

int main() {
    int mese;

    cout << "Inserire il mese: ";
    cin >> mese;

    if(mese <= 0 || mese > 12) {
        cout << "Mese non valido" << endl;
    } else if (mese == 1) {
        cout << "Gennaio" << endl;
    } else if (mese == 2) {
        cout << "Febbraio" << endl;
    } else if (mese == 3) {
        cout << "Marzo" << endl;
    } else if (mese == 4) {
        cout << "Aprile" << endl;
    } else if (mese == 5) {
        cout << "Maggio" << endl;
    } else if (mese == 6) {
        cout << "Giugno" << endl;
    } else if (mese == 7) {
        cout << "Luglio" << endl;
    } else if (mese == 8) {
        cout << "Agosto" << endl;
    } else if (mese == 9) {
        cout << "Settembre" << endl;
    } else if (mese == 10) {
        cout << "Ottobre" << endl;
    } else if (mese == 11) {
        cout << "Novembre" << endl;
    } else if (mese == 12) {
        cout << "Dicembre" << endl;
    }

    return 0;
}