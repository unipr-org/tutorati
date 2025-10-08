#include <iostream>
using namespace std;

int main() {
    float distanza;

    cout << "Inserire la distanza in chilometri (km): ";
    cin >> distanza;

    float metri = distanza * 1000;

    cout << "L'equivalente distanza in metri e': " <<
        metri
        << endl;

    return 0;
}