#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isPal(const string& s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

void partitionString(const string& s, int start, vector<string>& current, vector<vector<string>>& ans) {
    if (start == (int)s.size()) {
        ans.push_back(current);
        return;
    }
    for (int end = start; end < (int)s.size(); end++) {
        if (isPal(s, start, end)) {
            current.push_back(s.substr(start, end - start + 1));
            partitionString(s, end + 1, current, ans);
            current.pop_back();
        }
    }
}

int main() {
    string s;
    cout << "Enter a string: ";
    getline(cin, s);
    vector<string> current;
    vector<vector<string>> ans;
    partitionString(s, 0, current, ans);
    cout << "Palindrome partitions:" << endl;
    for (auto part : ans) {
        for (string x : part) cout << x << " ";
        cout << endl;
    }
    return 0;
}
