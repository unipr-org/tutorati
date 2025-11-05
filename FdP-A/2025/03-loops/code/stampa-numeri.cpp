#include <iostream>
using namespace std;

int main() {
    int i = 1;
    while (i <= 10) {
        cout << i << " ";
        i++;
    }

    cout << endl;

    i = 1;
    do {
        cout << i << " ";
        i++;
    } while (i <= 10);

    return 0;
}
