#include <iostream>
#include <string>
#include <vector>
using namespace std;

string mp[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void phoneComb(const string& digits, int i, string current, vector<string>& ans) {
    if (i == (int)digits.size()) {
        if (!current.empty()) ans.push_back(current);
        return;
    }
    string letters = mp[digits[i] - '0'];
    for (char c : letters) phoneComb(digits, i + 1, current + c, ans);
}

int main() {
    string digits;
    cout << "Enter digits from 2 to 9: ";
    cin >> digits;
    vector<string> ans;
    phoneComb(digits, 0, "", ans);
    cout << "Combinations:" << endl;
    for (string x : ans) cout << x << endl;
    return 0;
}
