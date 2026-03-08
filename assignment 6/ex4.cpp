#include <iostream>
using namespace std;

long long power(long long x, int y) {
    if (y == 0) return 1;
    return x * power(x, y - 1);
}

int main() {
    long long x;
    int y;
    cout << "Enter base: ";
    cin >> x;
    cout << "Enter exponent: ";
    cin >> y;
    cout << "Power = " << power(x, y);
    return 0;
}
