#include <iostream>
using namespace std;

#define DIM 100

int main(){
    char str[DIM];

    cout << "Inserire la stringa: ";
    cin.getline(str, DIM);

    int len = 0;
    while(str[len] != '\0') {
        len++;
    }

    int vocali = 0;
    for(int i = 0; i < len; i++) {
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u') {
            vocali++;
        }
        if(str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
            vocali++;
        }
    }

    cout << "Le vocali sono: " << vocali << endl;

    return 0;
}