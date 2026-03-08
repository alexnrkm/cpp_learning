#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindromeRec(const string& s, int l, int r) {
    if (l >= r) return true;
    if (s[l] != s[r]) return false;
    return isPalindromeRec(s, l + 1, r - 1);
}

int main() {
    string s, clean;
    cout << "Enter a string: ";
    getline(cin, s);
    for (char c : s) {
        if (c != ' ') clean += (char)tolower((unsigned char)c);
    }
    cout << (isPalindromeRec(clean, 0, (int)clean.size() - 1) ? "Palindrome" : "Not palindrome");
    return 0;
}
