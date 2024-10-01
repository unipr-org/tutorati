#include <iostream>
using namespace std;

int main() {
    float _distanza;

    cout << "Inserire la distanza in chilometri (km): ";
    cin >> _distanza;

    float _metri = _distanza * 1000;

    cout << "L'equivalente distanza in metri e': " << 
        _metri
        << endl;

    return 0;
}