#include <iostream>
#include <string>
using namespace std;

void generateSubsets(const string& s, int i, string current) {
    if (i == (int)s.size()) {
        cout << "\"" << current << "\"" << endl;
        return;
    }
    generateSubsets(s, i + 1, current);
    generateSubsets(s, i + 1, current + s[i]);
}

int main() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
    cout << "Subsets:" << endl;
    generateSubsets(s, 0, "");
    return 0;
}
