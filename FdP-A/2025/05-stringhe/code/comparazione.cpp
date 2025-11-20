#include <iostream>
using namespace std;

int main() {
    char a[200], b[200];
    cin.getline(a, 200);
    cin.getline(b, 200);

    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            cout << "Le stringhe sono diverse";
            return 0;
        }
        i++;
    }

    if (a[i] == '\0' && b[i] == '\0')
        cout << "Le stringhe sono uguali";
    else
        cout << "Le stringhe sono diverse";

    return 0;
}
