#include <iostream>
#include <cstring>
using namespace std;


bool trovaSottostringeComuni(char* str1, char* str2) {
    bool trovata = false;
    for(int i = 0; str1[i] != '\0'; i++){
        for(int len = 1; str1[i - 1 + len] != '\0'; len++) {

            char sottostringa[100];
            strncpy(sottostringa, str1 + i, len);
            sottostringa[len] = '\0';

            if(strstr(str2, sottostringa) != nullptr){
                trovata = true;
                cout << "Sottostringa: " << sottostringa << endl;
            }
        }
    }
    return trovata;
}

int main(){
    char str1[101], str2[101];

    cout << "Inserire la prima parola: ";
    cin.getline(str1, 100);
    cout << "Inserire la seconda parola: ";
    cin.getline(str2, 100);

    if(trovaSottostringeComuni(str1, str2))
        cout << "Esistono sottostringhe" << endl;

    return 0;
}