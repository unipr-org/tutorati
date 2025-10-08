#include <iostream>
using namespace std;

int main() {
    int _eta;

    cout << "Inserire l'eta': ";
    cin >> _eta;

    if(_eta < 0) {
        cout << "[ERRORE] L'eta' e' negativa!!" << endl;
    } else if (_eta < 12){
        cout << "Bambino" << endl;
    } else if (_eta < 18) {
        cout << "Adolescente" << endl;
    } else if (_eta < 65) {
        cout << "Adulto" << endl;
    } else {
        cout << "Anziano" << endl;
    }

    return 0;
}