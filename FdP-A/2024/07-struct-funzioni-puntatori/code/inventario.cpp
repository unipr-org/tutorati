#include <iostream>
using namespace std;

#define MAX_PRODOTTI 100

struct Prodotto {
    int id;
    char nome[51];
    float prezzo;
    int quantita;
};

bool inserisciProdotto(Prodotto prodotti[], int numeroProdotti) {
    if(numeroProdotti > MAX_PRODOTTI) {
        cout << "Inventario pieno!!!" << endl;
        return false;
    }

    cout << "Inserisci l'ID univoco del prodotto: ";
    cin >> prodotti[numeroProdotti].id;
    cin.ignore();

    cout << "Insesci il nome del prodotto: ";
    cin.getline(prodotti[numeroProdotti].nome, 50);

    cout << "Inserisci il prezzo unitario del prodotto: ";
    cin >> prodotti[numeroProdotti].prezzo;
    cin.ignore();

    cout << "Inserisci la quantita' del prodotto: ";
    cin >> prodotti[numeroProdotti].quantita;
    cin.ignore();

    return true;
}

void stampaProdotto(Prodotto prodotto) {
    cout << "ID: " << prodotto.id 
        << ", Nome: " << prodotto.nome 
        << ", Prezzo: " << prodotto.prezzo 
        << "€, Quantità: " << prodotto.quantita 
        << endl; 
} 

void stampaInventario(Prodotto prodotti[], int numeroProdotti) {
    if(numeroProdotti == 0) {
        cout << "Inventario vuoto!!" << endl;
        return;
    }

    cout << endl;
    cout << "=== Inventario === " << endl;
    for(int i = 0; i < numeroProdotti; i++){
        stampaProdotto(prodotti[i]);
    }
}

int ottieniScelta(){
    int scelta;

    cout << endl;
    cout << "=== Menu' === " << endl;
    cout << "1. Inserire un prodotto" << endl;
    cout << "2. Stampa inventario" << endl;
    cout << "3. Valore totale inventario" << endl;
    cout << "4. Cerca un prodotto" << endl;
    cout << "5. Modifica un prodotto" << endl;
    cout << "-1. Termina il programma" << endl;
    cout << "Scelta: ";
    cin >> scelta;
    cin.ignore();

    return scelta;
}

float calcolaValoreTotale(Prodotto prodotti[], int numeroProdotti) {
    float valoreTotale = 0.0;
    for(int i = 0; i < numeroProdotti; i++) {
        valoreTotale += (prodotti[i].prezzo * prodotti[i].quantita);
    }
    return valoreTotale;
}

Prodotto* cercaProdotto(Prodotto prodotti[], int numeroProdotti, int idCercato) {
    for(int i = 0; i < numeroProdotti; i++) {
        if(prodotti[i].id == idCercato) {
            return &prodotti[i];
        }
    }
    return nullptr;
}

// Uso il puntatore al prodotto
void modificaProdotto(Prodotto* prodotto) {
    cout << "Inserire il nuovo nome: ";
    cin.getline((*prodotto).nome, 50);

    cout << "Inserire il nuovo prezzo: ";
    cin >> (*prodotto).prezzo;
    cin.ignore();

    cout << "Inserire la nuova quantita': ";
    cin >> (*prodotto).quantita;
    cin.ignore();
}

// Passaggio per riferimento
void modificaProdotto(Prodotto& prodotto) {
    cout << "Inserire il nuovo nome: ";
    cin.getline(prodotto.nome, 50);

    cout << "Inserire il nuovo prezzo: ";
    cin >> prodotto.prezzo;
    cin.ignore();

    cout << "Inserire la nuova quantita': ";
    cin >> prodotto.quantita;
    cin.ignore();
}

int main(){
    Prodotto prodotti[MAX_PRODOTTI];
    int numeroProdotti = 0;

    int scelta = 0;
    do {
        scelta = ottieniScelta();

        switch (scelta) {
        case -1: 
            cout << "Addio!!" << endl;
            break;
            
        case 1: {
            if(inserisciProdotto(prodotti, numeroProdotti)) {
                numeroProdotti++;
            }
            break;
        }

        case 2: {
            stampaInventario(prodotti, numeroProdotti);
            break;
        }

        case 3: {
            if(numeroProdotti == 0) {
                cout << "Inventario vuoto!!" << endl;   
            } else {
                cout << "Il valore dell'inventario e': " 
                    << calcolaValoreTotale(prodotti, numeroProdotti) << endl;
            }
            break;
        }

        case 4: {
            int idCercato;
            cout << "Inserisci l'ID da cercare: ";
            cin >> idCercato;
            cin.ignore();

            Prodotto* p = cercaProdotto(prodotti, numeroProdotti, idCercato);
            if(p != nullptr) {
                stampaProdotto(*p);
            } else {
                cout << "L'ID non esiste nell'inventario!!" << endl;
            }
            break;
        }

        case 5: {
            int idCercato;
            cout << "Inserisci l'ID da modificare: ";
            cin >> idCercato;
            cin.ignore();

            Prodotto* p = cercaProdotto(prodotti, numeroProdotti, idCercato);
            if(p != nullptr) {
                // modificaProdotto(p);
                modificaProdotto(*p);
            } else {
                cout << "L'ID non esiste nell'inventario!!" << endl;
            }
            break;
        }

        default:
            cout << "Scelta non riconosciuta!! Riprovare." << endl;
            break;

        }
    } while(scelta != -1);

    return 0;
}