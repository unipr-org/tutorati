#include <iostream>
using namespace std;

int main() {
    float _distanza;

    cout << "Inserire la distanza in chilometri (km): ";
    cin >> _distanza;

    cout << "L'equivalente distanza in metri e': " << 
        _distanza * 1000 
        << endl;

    return 0;
}