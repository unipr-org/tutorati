#include <iostream>
using namespace std;

struct Prodotto {
    int id;
    char nome[50];
    float prezzo;
    int quantita;
};

int main() {
    Prodotto inventario[100];
    int n = 0; // numero prodotti attuali

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1) Aggiungi prodotto\n";
        cout << "2) Stampa inventario\n";
        cout << "3) Valore totale inventario\n";
        cout << "4) Esci\n";
        cout << "Scelta: ";

        int scelta;
        cin >> scelta;
        cin.ignore(); // pulisci buffer

        if (scelta == 1) {
            if (n == 100) {
                cout << "Inventario pieno!\n";
                continue;
            }

            cout << "ID prodotto: ";
            cin >> inventario[n].id;
            cin.ignore();

            cout << "Nome prodotto: ";
            cin.getline(inventario[n].nome, 50);

            cout << "Prezzo unitario: ";
            cin >> inventario[n].prezzo;

            cout << "Quantita: ";
            cin >> inventario[n].quantita;

            n++;
            cout << "Prodotto aggiunto!\n";
        }

        else if (scelta == 2) {
            cout << "\n--- INVENTARIO ---\n";
            for (int i = 0; i < n; i++) {
                cout << "ID: " << inventario[i].id
                     << ", Nome: " << inventario[i].nome
                     << ", Prezzo: " << inventario[i].prezzo
                     << ", Quantita: " << inventario[i].quantita << endl;
            }
        }

        else if (scelta == 3) {
            float totale = 0;
            for (int i = 0; i < n; i++) {
                totale += inventario[i].prezzo * inventario[i].quantita;
            }
            cout << "Valore totale: " << totale << endl;
        }

        else if (scelta == 4) {
            cout << "Uscita.\n";
            break;
        }

        else {
            cout << "Scelta non valida.\n";
        }
    }

    return 0;
}

