#include <iostream>
using namespace std;

int main() {
    int a, b, c;

    cout << "Inserisci il primo valore: ";
    cin >> a;

    cout << "Inserisci il secondo valore: ";
    cin >> b;

    cout << "Inserisci il terzo valore: ";
    cin >> c;

    int max = a;
    int min = a;

    if(b > max)
        max = b;
    if(c > max)
        max = c;

    if(b < min)
        min = b;
    if(c < min)
        min = c;

    int risultato = max - min;

    cout << "Risultato: " << risultato << endl;

    return 0;
}