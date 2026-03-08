#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canPartition(vector<int>& nums, vector<int>& bucket, int index, int target) {
    if (index == (int)nums.size()) return true;
    for (int i = 0; i < (int)bucket.size(); i++) {
        if (bucket[i] + nums[index] > target) continue;
        bucket[i] += nums[index];
        if (canPartition(nums, bucket, index + 1, target)) return true;
        bucket[i] -= nums[index];
        if (bucket[i] == 0) break;
    }
    return false;
}

int main() {
    int n, k;
    cout << "Enter number of elements: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Enter " << n << " elements: ";
    int sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }
    cout << "Enter K: ";
    cin >> k;
    if (k <= 0 || sum % k != 0) {
        cout << "False";
        return 0;
    }
    sort(nums.rbegin(), nums.rend());
    vector<int> bucket(k, 0);
    cout << (canPartition(nums, bucket, 0, sum / k) ? "True" : "False");
    return 0;
}
