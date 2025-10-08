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

    int parole = 0;
    bool inParola = false;

    for(int i = 0; i < len; i++) {
        if(str[i] == ' '){
            inParola = false;
        } else if(str[i] != ' ' && !inParola) {
            parole++;
            inParola = true;
        }
    }

    cout << "Numero parole: " << parole << endl;


    return 0;
}