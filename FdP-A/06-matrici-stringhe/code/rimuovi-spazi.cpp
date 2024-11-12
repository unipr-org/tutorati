#include <iostream>
using namespace std;

#define DIM 100

int main(){
    char str[DIM];

    cout << "Inserire la stringa: ";
    cin.getline(str, DIM);

    int len = 0, i = 0;
    while(str[len] != '\0') {
        len++;
    }

    cout << "Stringa iniziale con spazi \"" << str << "\"" << endl;

    // Conto quanti spazi ci sono all'inizio
    while(str[i] == ' '){
        i++;
    }

    if (i > 0) {
        // Shift a sinistra per rimuovere gli spazi iniziali
        for (int j = 0; j < len - i; j++) {
            str[j] = str[j + i];
        }
        str[len - i] = '\0'; // Aggiorno il terminatore di stringa
        len -= i; // Aggiorno la lunghezza della stringa
    }

    for(int z = i; z < len - 1; z++){
        if(str[z] == ' ' && str[z + 1] == ' ') {

            // Shift a sinistra
            for(int s = z + 1; s < len - 1; s++) {
                str[s] = str[s + 1];
            }
            len--;
            z--;

        }
    }

    // Rimuove lo spazio finale (se esiste)
    if (len > 0 && str[len - 1] == ' ') {
        len--;
    }

    str[len] = '\0';

    cout << "Stringa finale senza spazi \"" << str << "\"" << endl;

    return 0;
}