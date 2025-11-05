#include <iostream>
using namespace std;

int main() {
    int n, invertito = 0;
    cout << "Inserisci un numero: ";
    cin >> n;

    while (n > 0) {
        invertito = invertito * 10 + (n % 10);
        n /= 10;
    }

    cout << "Numero invertito: " << invertito << endl;
    return 0;
}
