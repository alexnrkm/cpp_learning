#include <iostream>
using namespace std;

bool isPrimeRec(int n, int d) {
    if (n < 2) return false;
    if (d * d > n) return true;
    if (n % d == 0) return false;
    return isPrimeRec(n, d + 1);
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << (isPrimeRec(n, 2) ? "Prime" : "Not prime");
    return 0;
}
