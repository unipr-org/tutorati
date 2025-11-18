#include <iostream>
using namespace std;

int main() {
    char s[200];
    cout << "Inserisci una stringa: ";
    cin.getline(s, 200);

    int maxLen = 0;
    int currLen = 0;
    int maxStart = 0;
    int currStart = 0;

    for (int i = 0; ; i++) {
        if (s[i] != ' ' && s[i] != '\0') {
            if (currLen == 0)
                currStart = i;
            currLen++;
        } else {
            if (currLen > maxLen) {
                maxLen = currLen;
                maxStart = currStart;
            }
            currLen = 0;
        }

        if (s[i] == '\0') break;
    }

    cout << "Parola piu' lunga: ";
    for (int i = 0; i < maxLen; i++)
        cout << s[maxStart + i];

    cout << " (lunghezza = " << maxLen << ")" << endl;

    return 0;
}
