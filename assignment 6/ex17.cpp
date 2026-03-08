#include <iostream>
#include <string>
using namespace std;

string reverseString(const string& s) {
    if (s.empty()) return "";
    return reverseString(s.substr(1)) + s[0];
}

int main() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
    cout << "Reversed string = " << reverseString(s);
    return 0;
}
