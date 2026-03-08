#include <iostream>
using namespace std;

void reverseDigits(long long n) {
    if (n < 10) {
        cout << n;
        return;
    }
    cout << n % 10;
    reverseDigits(n / 10);
}

int main() {
    long long n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Reversed digits = ";
    if (n < 0) {
        cout << "-";
        n = -n;
    }
    reverseDigits(n);
    return 0;
}
