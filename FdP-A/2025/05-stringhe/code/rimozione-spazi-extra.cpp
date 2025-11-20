#include <iostream>
using namespace std;

int main() {
    char s[300], out[300];
    cin.getline(s, 300);

    int i = 0, j = 0;

    // Skippa spazi iniziali
    while (s[i] == ' ')
        i++;

    bool spazio = false;

    while (s[i] != '\0') {
        if (s[i] != ' ') {
            out[j++] = s[i];
            spazio = false;
        } else {
            if (!spazio) {
                out[j++] = ' ';
                spazio = true;
            }
        }
        i++;
    }

    // Rimuovi eventuale spazio finale
    if (j > 0 && out[j - 1] == ' ')
        j--;

    out[j] = '\0';

    cout << out << endl;
    return 0;
}
