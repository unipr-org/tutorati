#include <iostream>
using namespace std;

int main() {
    char s[200];
    cout << "Inserisci una stringa: ";
    cin.getline(s, 200);

    char out[200];
    int j = 0;
    bool spazioPrecedente = true;

    // Rimuovi spazi extra e spazi all'inizio
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') {
            out[j++] = s[i];
            spazioPrecedente = false;
        } else {
            if (!spazioPrecedente) {
                out[j++] = ' ';
            }
            spazioPrecedente = true;
        }
    }

    // Rimuove eventuale spazio finale
    if (j > 0 && out[j-1] == ' ')
        j--;

    out[j] = '\0';

    cout << "Stringa pulita: \"" << out << "\"" << endl;
    return 0;
}

