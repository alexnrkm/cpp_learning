#include <iostream>
#include <string>
using namespace std;

void swapChar(char& a, char& b) {
    char t = a;
    a = b;
    b = t;
}

void permutations(string& s, int i) {
    if (i == (int)s.size()) {
        cout << s << endl;
        return;
    }
    for (int j = i; j < (int)s.size(); j++) {
        swapChar(s[i], s[j]);
        permutations(s, i + 1);
        swapChar(s[i], s[j]);
    }
}

int main() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
    cout << "Permutations:" << endl;
    permutations(s, 0);
    return 0;
}
