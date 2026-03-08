#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void subsetSum(vector<int>& arr, int target, int index, vector<int>& current, vector<vector<int>>& ans) {
    if (target == 0) {
        ans.push_back(current);
        return;
    }
    for (int i = index; i < (int)arr.size(); i++) {
        if (i > index && arr[i] == arr[i - 1]) continue;
        if (arr[i] > target) break;
        current.push_back(arr[i]);
        subsetSum(arr, target - arr[i], i + 1, current, ans);
        current.pop_back();
    }
}

int main() {
    int n, target;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << "Enter target sum: ";
    cin >> target;
    sort(arr.begin(), arr.end());
    vector<int> current;
    vector<vector<int>> ans;
    subsetSum(arr, target, 0, current, ans);
    cout << "Subsets:" << endl;
    for (auto v : ans) {
        for (int x : v) cout << x << " ";
        cout << endl;
    }
    return 0;
}
