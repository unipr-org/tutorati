#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Inserisci un numero: ";
    cin >> n;

    bool primo = true;
    int i = 2;

    while (i <= n / 2) {
        if (n % i == 0) {
            primo = false;
            break;
        }
        i++;
    }

    if (primo)
        cout << "Il numero e' primo (while)" << endl;
    else
        cout << "Il numero non e' primo (while)" << endl;

    i = 2;
    primo = true;

    if (n > 1) {
        do {
            if (n % i == 0) {
                primo = false;
                break;
            }
            i++;
        } while (i <= n / 2);
    } else {
        primo = false; // 0 e 1 non sono primi
    }

    if (primo)
        cout << "Il numero e' primo (do-while)" << endl;
    else
        cout << "Il numero non e' primo (do-while)" << endl;

    return 0;
}
