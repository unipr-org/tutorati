#include <iostream>
using namespace std;

int main(){
    int n;
    do {
        cout << "Inserire la dimensione del primo array: ";
        cin >> n;
    } while(n < 1);

    int array1[n];

    for(int i = 0; i < n; i++) {
        cout << "Inserisci il " << i + 1 << " elemento: ";
        cin >> array1[i];
    }

    int m;
    do {
        cout << "Inserire la dimensione secondo array: ";
        cin >> m;
    } while(m < 1);

    int array2[m];

    for(int i = 0; i < m; i++) {
        cout << "Inserisci il " << i + 1 << " elemento: ";
        cin >> array2[i];
    }

    int unione[n + m];
    int k = 0;

    // unione
    for(int i = 0; i < n; i++){
        unione[k] = array1[i];
        k++;
    }
    for(int i = 0; i < m; i++){
        unione[k] = array2[i];
        k++;
    }

    // stampa
    cout << "Unione con (possibili) duplicati" << endl;
    for(int i = 0; i < k; i++){
        cout << unione[i] << " ";
    }
    cout << endl;

    // eliminazione duplicati
    for(int i = 0; i < k; i++){
        for(int j = i + 1; j < k; j++){
            if(unione[i] == unione[j]){
                for(int z = j; z < k - 1; z++){
                    unione[z] = unione[z + 1];
                }
                k--;
            }
        }
    }

    // stampa
    cout << "Unione senza duplicati" << endl;
    for(int i = 0; i < k; i++){
        cout << unione[i] << " ";
    }
    cout << endl;

    return 0;
}