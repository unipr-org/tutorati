#include <iostream>
using namespace std;

int main() {
    cout << "do-while" << endl;
    int i = 0;
    do {
        i++;
        cout << i << endl;
    } while (i < 10);

    cout << "while" << endl;
    int j = 0;
    while(j < 10){
        j++;
        cout << j << endl;
    }

    cout << "for" << endl;
    int z;
    for(z = 1; z <= 10; z++) {
        cout << z << endl;
    }

    return 0;
}