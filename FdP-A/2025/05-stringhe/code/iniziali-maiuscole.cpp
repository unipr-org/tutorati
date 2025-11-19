#include <iostream>
using namespace std;

int main() {
    char testo[200];

    cout << "Inserisci una stringa: ";
    cin.getline(testo, 200);

    int i = 0;
    while (testo[i] != '\0') {
        if (testo[i] >= 'a' && testo[i] <= 'z') {
            if (i == 0 || testo[i - 1] == ' ') {
                testo[i] = testo[i] - 32;
            }
        }
        i++;
    }

    cout << "Stringa modificata: " << testo << endl;

    return 0;
}