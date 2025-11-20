#include <iostream>
using namespace std;

int main() {
    char s[200], cerca[50], sost[50];
    cout << "Inserisci la stringa: ";
    cin.getline(s, 200);

    cout << "Parola da cercare: ";
    cin.getline(cerca, 50);

    cout << "Parola sostitutiva: ";
    cin.getline(sost, 50);

    char out[300];
    int j = 0;

    int lenCerca = 0;
    while (cerca[lenCerca] != '\0')
        lenCerca++;

    for (int i = 0; s[i] != '\0'; ) {
        bool uguale = true;
        for (int k = 0; k < lenCerca; k++) {
            if (s[i + k] == '\0' || s[i + k] != cerca[k]) {
                uguale = false;
                break;
            }
        }

        if (uguale) {
            int k = 0;
            while (sost[k] != '\0') {
                out[j++] = sost[k++];
            }
            i += lenCerca;
        } else {
            out[j++] = s[i++];
        }
    }

    out[j] = '\0';

    cout << "Risultato: " << out << endl;

    return 0;
}
