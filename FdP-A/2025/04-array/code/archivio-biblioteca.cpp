#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Quanti libri vuoi inserire? ";
    cin >> n;

    int id[n];
    int anno[n];

    for (int i = 0; i < n; i++) {
        cout << "Inserisci l'ID del libro #" << (i + 1) << ": ";
        cin >> id[i];
        cout << "Inserisci l'anno di pubblicazione: ";
        cin >> anno[i];
    }

    int X;
    cout << "\nInserisci un anno X: ";
    cin >> X;

    cout << "\nLibri pubblicati dopo l'anno " << X << ":\n";
    for (int i = 0; i < n; i++) {
        if (anno[i] > X) {
            cout << "ID " << id[i] << " - Anno " << anno[i] << endl;
        }
    }

    int indiceMin = 0;
    for (int i = 1; i < n; i++) {
        if (anno[i] < anno[indiceMin]) {
            indiceMin = i;
        }
    }

    cout << "\nLibro piu' vecchio:\n";
    cout << "ID " << id[indiceMin] << " - Anno " << anno[indiceMin] << endl;

    return 0;
}
