#include <iostream>
using namespace std;

int sumOfDigits(long long n) {
    if (n < 0) n = -n;
    if (n == 0) return 0;
    return n % 10 + sumOfDigits(n / 10);
}

int main() {
    long long n;
    cout << "Enter an integer: ";
    cin >> n;
    cout << "Sum of digits = " << sumOfDigits(n);
    return 0;
}
