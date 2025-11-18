#include <iostream>
using namespace std;

int main() {
    char s[200];
    cout << "Inserisci una stringa: ";
    cin.getline(s, 200);

    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
            c=='A' || c=='E' || c=='I' || c=='O' || c=='U') {
            count++;
        }
    }

    cout << "Vocali: " << count << endl;
    return 0;
}

