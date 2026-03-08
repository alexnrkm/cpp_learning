#include <iostream>
#include <string>
using namespace std;

string checkNum(int n) {
    if (n < 0) n = -n;
    if (n == 0) return "even";
    if (n == 1) return "odd";
    return checkNum(n - 2);
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "The number is " << checkNum(n);
    return 0;
}
