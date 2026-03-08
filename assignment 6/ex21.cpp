#include <iostream>
#include <string>
#include <vector>
using namespace std;

void permute(string& s, int i, vector<string>& ans) {
    if (i == (int)s.size()) {
        ans.push_back(s);
        return;
    }
    for (int j = i; j < (int)s.size(); j++) {
        swap(s[i], s[j]);
        permute(s, i + 1, ans);
        swap(s[i], s[j]);
    }
}

int main() {
    string s;
    vector<string> ans;
    cout << "Enter a string: ";
    getline(cin, s);
    permute(s, 0, ans);
    cout << "All permutations:" << endl;
    for (string x : ans) cout << x << endl;
    return 0;
}
