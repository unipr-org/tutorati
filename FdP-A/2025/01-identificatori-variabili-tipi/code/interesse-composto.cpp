#include <iostream>
#include <cmath>

using namespace std;

int main() {
    float capitaleIniziale, tassoAnnuo;
    int numeroAnni;

    cout << "Inserire il capitale iniziale: ";
    cin >> capitaleIniziale;

    cout << "Inserire il tasso annuo: ";
    cin >> tassoAnnuo;

    cout << "Inserire il numero di anni: ";
    cin >> numeroAnni;

    float capitaleFinale = capitaleIniziale * pow(1 + tassoAnnuo / 100, numeroAnni);

    cout << "L'importo totale accumulato e': " <<
        capitaleFinale
        << endl;

    return 0;
}