#include <iostream>
using namespace std;

int main() {
    float distanza, tempo;

    cout << "Inserire la distanza percorsa: ";
    cin >> distanza;

    cout << "Inserire il tempo impiegato: ";
    cin >> tempo;

    float velocitaMediaChilometri = distanza / tempo;

    cout << "La velocita' media in km/h e': " <<
        velocitaMediaChilometri
        << endl;

    float velocitaMediaMetri = velocitaMediaChilometri * 0.27778;

    cout << "La velocita' media in m/s e': " <<
        velocitaMediaMetri
        << endl;

    return 0;
}