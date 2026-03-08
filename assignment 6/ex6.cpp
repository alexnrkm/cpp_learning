#include <iostream>
using namespace std;

int gcdRec(int a, int b) {
    if (b == 0) return a < 0 ? -a : a;
    return gcdRec(b, a % b);
}

int main() {
    int a, b;
    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;
    cout << "GCD = " << gcdRec(a, b);
    return 0;
}
