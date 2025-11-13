#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Inserisci due numeri: ";
    cin >> a >> b;

    int max = (a > b) ? a : b;

    while (true) {
        if (max % a == 0 && max % b == 0) {
            cout << "MCM: " << max << endl;
            break;
        }
        max++;
    }

    return 0;
}
