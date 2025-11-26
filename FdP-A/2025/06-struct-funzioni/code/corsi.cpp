#include <iostream>
using namespace std;

struct Studente {
    char nome[50];
    int voto;
};

struct SchedaCorso {
    float media;
    int votoMassimo;
    Studente miglioreStudente;
};

float mediaClasse(Studente corso[], int n) {
    float somma = 0;
    for (int i = 0; i < n; i++) {
        somma += corso[i].voto;
    }
    if (n > 0)
        return (float) somma / n;
    return 0.0;
}

Studente miglioreStudente(Studente corso[], int n) {
    Studente migliore = corso[0];
    for (int i = 1; i < n; i++) {
        if (corso[i].voto > migliore.voto) {
            migliore = corso[i];
        }
    }
    return migliore;
}

SchedaCorso generaScheda(Studente corso[], int n) {
    SchedaCorso scheda;
    scheda.media = mediaClasse(corso, n);
    scheda.miglioreStudente = miglioreStudente(corso, n);
    scheda.votoMassimo = scheda.miglioreStudente.voto;
    return scheda;
}

int main() {
    int n;
    cout << "Numero di studenti: ";
    cin >> n;

    Studente arr[40];

    for (int i = 0; i < n; i++) {
        cout << "Nome studente " << (i + 1) << ": ";
        cin.ignore();
        cin.getline(arr[i].nome, 50);

        cout << "Voto studente " << (i + 1) << ": ";
        cin >> arr[i].voto;
    }

    SchedaCorso sc = generaScheda(arr, n);

    cout << "Media: " << sc.media << endl;
    cout << "Voto piu alto: " << sc.votoMassimo << endl;
    cout << "Migliore: " << sc.miglioreStudente.nome << endl;

    return 0;
}
