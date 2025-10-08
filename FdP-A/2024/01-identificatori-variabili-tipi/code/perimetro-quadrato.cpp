#include <iostream>
using namespace std;

int main() {
    int _lato;

    cout << "Inserire la lunghezza del lato del quadrato: ";
    cin >> _lato;

    cout << "Il perimetro del quadrato e': " << 
        _lato * 4 
        << endl;

    return 0;
}