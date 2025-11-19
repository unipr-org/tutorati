#include <iostream>
using namespace std;

int main() {
    char s[300];
    cin.getline(s, 300);

    int maxLen = 0, maxStart = 0;
    int len = 0, start = 0;

    int i = 0;
    while (s[i] != '\0') {
        if (s[i] != ' ') {
            if (len == 0)
                start = i;
            len++;
        } else {
            if (len > maxLen) {
                maxLen = len;
                maxStart = start;
            }
            len = 0;
        }

        i++;
    }

    // Dopo la stringa potrebbe esserci una parola che non è stata chiusa da uno spazio
    if (len > maxLen) {
        maxLen = len;
        maxStart = start;
    }

    // Stampa della parola più lunga
    for (int k = 0; k < maxLen; k++)
        cout << s[maxStart + k];

    cout << " (" << maxLen << ")";

    return 0;
}
