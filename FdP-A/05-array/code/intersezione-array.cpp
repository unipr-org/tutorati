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

    int min = (n > m) ? m : n;

    int intersezione[min];
    int k = 0;

    // intersezione
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(array1[i] == array2[j]){
                intersezione[k] = array1[i];
                k++;
            }
        }
    }

    // stampa
    cout << "Intersezione con (possibili) duplicati" << endl;
    for(int i = 0; i < k; i++){
        cout << intersezione[i] << " ";
    }
    cout << endl;

    // eliminazione duplicati
    for(int i = 0; i < k; i++){
        for(int j = i + 1; j < k; j++){
            if(intersezione[i] == intersezione[j]){
                for(int z = j; z < k - 1; z++){
                    intersezione[z] = intersezione[z + 1];
                }
                k--;
            }
        }
    }

    // stampa
    cout << "Intersezione senza duplicati" << endl;
    for(int i = 0; i < k; i++){
        cout << intersezione[i] << " ";
    }
    cout << endl;

    return 0;
}