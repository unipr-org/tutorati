#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Quanti esami hai sostenuto? ";
    cin >> n;

    int codice[n];
    int voto[n];

    for (int i = 0; i < n; i++) {
        cout << "Inserisci il codice dell'esame #" << (i + 1) << ": ";
        cin >> codice[i];
        cout << "Inserisci il voto ottenuto: ";
        cin >> voto[i];
    }

    int somma = 0;
    int superati = 0;

    for (int i = 0; i < n; i++) {
        somma += voto[i];
        if (voto[i] >= 18)
            superati++;
    }

    double media = (double) somma / n;

    cout << "\n--- Riepilogo ---\n";
    for (int i = 0; i < n; i++) {
        cout << "Esame codice " << codice[i] << ": voto " << voto[i] << endl;
    }

    cout << "Media voti: " << media << endl;
    cout << "Esami superati: " << superati << endl;

    return 0;
}
