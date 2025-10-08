#include <iostream>
using namespace std;

int main() {
    int lato;

    cout << "Inserire la lunghezza del lato del quadrato: ";
    cin >> lato;

    cout << "Il perimetro del quadrato e': " <<
        lato * 4
        << endl;

    return 0;
}