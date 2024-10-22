#include <iostream>
using namespace std;

int main(){
    int _altezza;

    cout << "Inserire l'altezza dell'albero di Natale: ";
    cin >> _altezza;

    while(_altezza < 0) {
        cout << "Errore" << endl;
        cout << "Inserire l'altezza dell'albero di Natale: ";
        cin >> _altezza;
    }

    for(int i = 1; i <= _altezza; i++){
        for(int j = 1; j <= _altezza - i; j++) {
            cout << " ";
        }

        for(int z = 1; z <= 2 * i - 1; z++){
            cout << "*";
        }
        cout << endl;
    }

    for(int i = 1; i < _altezza; i++) {
        cout << " ";
    }
    cout << "*" << endl;

    return 0;
}