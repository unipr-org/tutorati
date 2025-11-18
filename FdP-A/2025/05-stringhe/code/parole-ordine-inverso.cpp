#include <iostream>
using namespace std;

int main() {
    char testo[200];

    cout << "Inserisci una stringa: ";
    cin.getline(testo, 200);

    int len = 0;
    while (testo[len] != '\0') {
        len++;
    }

    int fineParola = len;

    cout << "Parole invertite: ";

    for (int i = len - 1; i >= 0; i--) {

        if (testo[i] == ' ' || i == 0) {

            int inizioParola;
            if (i == 0) {
                inizioParola = 0;
            } else {
                inizioParola = i + 1;
            }

            for (int k = inizioParola; k < fineParola; k++) {
                cout << testo[k];
            }
            cout << " ";

            fineParola = i;
        }
    }
    cout << endl;

    return 0;
}