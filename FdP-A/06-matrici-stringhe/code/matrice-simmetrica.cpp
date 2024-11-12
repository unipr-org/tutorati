#include <iostream>
using namespace std;

int main(){
    int dim;

    do {
        cout << "Inserire la dimensione della matrice: ";
        cin >> dim;
    } while(dim < 1);

    int matrice[dim][dim];

    cout << "Inserire i valori della matrice: " << endl;
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            cout << "Elemento (" << r + 1 << ", " << c + 1 << "): ";
            cin >> matrice[r][c];
        }
    }

    // Stampa della matrice
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            cout << matrice[r][c] << " "; 
        }
        cout << endl;
    }

    bool simmetrica = true;
    for (int r = 0; r < dim; r++) {
        for (int c = 0; c < dim; c++) {
            if(matrice[r][c] != matrice[c][r]) {
                simmetrica = false;
                break;
            }
        }
        if(!simmetrica) {
            break;
        }
    }

    if(simmetrica) {
        cout << "Matrice simmetrica" << endl;
    } else {
        cout << "Matrice non simmetrica" << endl;
    }

    return 0;
}