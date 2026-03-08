#include <iostream>
using namespace std;

void convertToBinary(int n) {
    if (n <= 1) {
        cout << n;
        return;
    }
    convertToBinary(n / 2);
    cout << n % 2;
}

int main() {
    int n;
    cout << "Enter a non-negative number: ";
    cin >> n;
    cout << "Binary = ";
    convertToBinary(n);
    return 0;
}
