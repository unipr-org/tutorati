#include <iostream>
using namespace std;

int main(){
    int L, M, N;

    do {
        cout << "Inserire la dimensione di L: ";
        cin >> L;
    } while(L < 1);

    do {
        cout << "Inserire la dimensione di M: ";
        cin >> M;
    } while(M < 1);

    do {
        cout << "Inserire la dimensione di N: ";
        cin >> N;
    } while(N < 1);

    int matrice1[L][M];
    int matrice2[M][N];

    cout << "Inserire i valori della matrice " << L << " x " << M << ": " << endl;
    for (int r = 0; r < L; r++) {
        for (int c = 0; c < M; c++) {
            cout << "Elemento (" << r + 1 << ", " << c + 1 << "): ";
            cin >> matrice1[r][c];
        }
    }

    cout << "Inserire i valori della matrice " << M << " x " << N << ": " << endl;
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < N; c++) {
            cout << "Elemento (" << r + 1 << ", " << c + 1 << "): ";
            cin >> matrice2[r][c];
        }
    }

    // Stampa della matrice1
    cout << "Matrice 1" << endl;
    for (int r = 0; r < L; r++) {
        for (int c = 0; c < M; c++) {
            cout << matrice1[r][c] << " "; 
        }
        cout << endl;
    }

    // Stampa della matrice2
    cout << "Matrice 2" << endl;
    for (int r = 0; r < M; r++) {
        for (int c = 0; c < N; c++) {
            cout << matrice2[r][c] << " "; 
        }
        cout << endl;
    }

    int prodotto[L][N];

    for (int r = 0; r < L; r++) {
        for (int c = 0; c < N; c++) {
            prodotto[r][c] = 0;
        }
    }

    for(int l = 0; l < L; l++){
        for(int n = 0; n < N; n++) {
            for(int m = 0; m < M; m++) {
                prodotto[l][n] += matrice1[l][m] * matrice2[m][n];
            }
        }
    }

    cout << "Risultato" << endl;
    for (int r = 0; r < L; r++) {
        for (int c = 0; c < N; c++) {
            cout << prodotto[r][c] << " "; 
        }
        cout << endl;
    }


    return 0;
}