#include <iostream>
using namespace std;

int main() {
    int n, i = 1, count = 0;
    cout << "Inserisci un numero: ";
    cin >> n;

    cout << "Divisori (while): ";
    while (i <= n) {
        if (n % i == 0) {
            cout << i << " ";
            count++;
        }
        i++;
    }

    cout << endl;
    cout << "Totale: " << count << endl;

    i = 1;
    count = 0;
    cout << "Divisori (do-while): ";
    do {
        if (n % i == 0) {
            cout << i << " ";
            count++;
        }
        i++;
    } while (i <= n);

    cout << endl;
    cout << "Totale: " << count << endl;

    return 0;
}
