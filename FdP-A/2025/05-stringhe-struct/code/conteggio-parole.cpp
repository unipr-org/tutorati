#include <iostream>
using namespace std;

int main() {
    char s[200];
    cout << "Inserisci una stringa: ";
    cin.getline(s, 200);

    int parole = 0;
    bool dentroParola = false;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ' && !dentroParola) {
            dentroParola = true;
            parole++;
        }
        if (s[i] == ' ') {
            dentroParola = false;
        }
    }

    cout << "Parole: " << parole << endl;
    return 0;
}

