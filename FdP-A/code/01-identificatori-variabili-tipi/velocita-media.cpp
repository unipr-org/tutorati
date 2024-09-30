#include <iostream>
using namespace std;

int main() {
    float _distanza, _tempo;

    cout << "Inserire la distanza percorsa: ";
    cin >> _distanza;

    cout << "Inserire il tempo impiegato: ";
    cin >> _tempo;

    cout << "La velocita' media in km/h e': " << 
        _distanza / _tempo 
        << endl;
    
    cout << "La velocita' media in m/s e': " << 
        _distanza / _tempo * 0.27778 
        << endl;

    return 0;
}