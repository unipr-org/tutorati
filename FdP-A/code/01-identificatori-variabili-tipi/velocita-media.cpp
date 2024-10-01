#include <iostream>
using namespace std;

int main() {
    float _distanza, _tempo;

    cout << "Inserire la distanza percorsa: ";
    cin >> _distanza;

    cout << "Inserire il tempo impiegato: ";
    cin >> _tempo;

    float _velocitaMediaChilometri = _distanza / _tempo;
    
    cout << "La velocita' media in km/h e': " << 
        _velocitaMediaChilometri
        << endl;
    
    float _velocitaMediaMetri = _velocitaMediaChilometri * 0.27778;

    cout << "La velocita' media in m/s e': " << 
        _velocitaMediaMetri
        << endl;

    return 0;
}