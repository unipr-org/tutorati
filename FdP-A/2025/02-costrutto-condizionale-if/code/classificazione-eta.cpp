#include <iostream>
using namespace std;

int main() {
    int eta;

    cout << "Inserire l'eta': ";
    cin >> eta;

    if(eta < 0) {
        cout << "L'eta' e' negativa" << endl;
    } else if (eta < 12){
        cout << "Bambino" << endl;
    } else if (eta < 18) {
        cout << "Adolescente" << endl;
    } else if (eta < 65) {
        cout << "Adulto" << endl;
    } else {
        cout << "Anziano" << endl;
    }

    return 0;
}