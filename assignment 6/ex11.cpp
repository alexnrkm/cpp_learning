#include <iostream>
using namespace std;

int multiplyRec(int a, int b) {
    if (b == 0) return 0;
    if (b < 0) return -multiplyRec(a, -b);
    return a + multiplyRec(a, b - 1);
}

int main() {
    int a, b;
    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;
    cout << "Result = " << multiplyRec(a, b);
    return 0;
}
