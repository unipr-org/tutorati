#include <iostream>
#include <cmath>

using namespace std;

int main() {
    float _capitaleIniziale, _tassoAnnuo;
    int _numeroAnni;

    cout << "Inserire il capitale iniziale: ";
    cin >> _capitaleIniziale;

    cout << "Inserire il tasso annuo: ";
    cin >> _tassoAnnuo;

    cout << "Inserire il numero di anni: ";
    cin >> _numeroAnni;

    float _capitaleFinale = _capitaleIniziale * pow(1 + _tassoAnnuo / 100, _numeroAnni);

    cout << "L'importo totale accumulato e': " << 
        _capitaleFinale
        << endl;

    return 0;
}