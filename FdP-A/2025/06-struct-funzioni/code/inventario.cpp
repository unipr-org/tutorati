#include <iostream>
using namespace std;

struct Prodotto {
    int id;
    char nome[50];
    double prezzo;
    int quantita;
};

void inserisciProdotto(Prodotto magazzino[], int n) {
    if (n >= 100) {
        cout << "Magazzino pieno." << endl;
        return;
    }
    cout << "Inserisci ID: ";
    cin >> magazzino[n].id;
    cout << "Inserisci Nome: ";
    cin.ignore();
    cin.getline(magazzino[n].nome, 50);
    cout << "Inserisci Prezzo: ";
    cin >> magazzino[n].prezzo;
    cout << "Inserisci Quantita': ";
    cin >> magazzino[n].quantita;
}

void stampaInventario(Prodotto magazzino[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "ID: " << magazzino[i].id
             << " - Nome: " << magazzino[i].nome
             << " - Prezzo: " << magazzino[i].prezzo
             << " - Qta: " << magazzino[i].quantita << endl;
    }
}

double calcolaValoreTotale(Prodotto magazzino[], int n) {
    double totale = 0;
    for (int i = 0; i < n; i++) {
        totale += (magazzino[i].prezzo * magazzino[i].quantita);
    }
    return totale;
}

bool cercaProdotto(Prodotto magazzino[], int n, int idCercato) {
    for (int i = 0; i < n; i++) {
        if (magazzino[i].id == idCercato) {
            return true;
        }
    }
    return false;
}

int main() {
    Prodotto magazzino[100];
    int numProdotti = 0;
    int scelta = 0;

    while (scelta != -1) {
        cout << "\n1. Inserisci prodotto" << endl;
        cout << "2. Stampa inventario" << endl;
        cout << "3. Valore totale magazzino" << endl;
        cout << "4. Cerca prodotto per ID" << endl;
        cout << "-1. Esci" << endl;
        cout << "Scelta: ";
        cin >> scelta;

        if (scelta == 1) {
            inserisciProdotto(magazzino, numProdotti);
            numProdotti++;
        } else if (scelta == 2) {
            stampaInventario(magazzino, numProdotti);
        } else if (scelta == 3) {
            cout << "Valore totale: " << calcolaValoreTotale(magazzino, numProdotti) << endl;
        } else if (scelta == 4) {
            int id;
            cout << "Inserisci ID da cercare: ";
            cin >> id;
            if (cercaProdotto(magazzino, numProdotti, id)) {
                cout << "Prodotto trovato!" << endl;
                for(int i = 0; i < numProdotti; i++) {
                    if(magazzino[i].id == id) {
                        cout << "Dettagli: " << magazzino[i].nome
                             << ", Prezzo: " << magazzino[i].prezzo << endl;
                    }
                }
            } else {
                cout << "Prodotto non trovato." << endl;
            }
        } else if (scelta != -1) {
            cout << "Scelta non valida." << endl;
        }
    }

    return 0;
}
