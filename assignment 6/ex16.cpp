#include <iostream>
#include <string>
using namespace std;

int countChar(const string& s, char ch, int i) {
    if (i == (int)s.size()) return 0;
    return (s[i] == ch) + countChar(s, ch, i + 1);
}

int main() {
    string s;
    char ch;
    cout << "Enter a string: ";
    getline(cin, s);
    cout << "Enter a character: ";
    cin >> ch;
    cout << "Occurrences = " << countChar(s, ch, 0);
    return 0;
}
