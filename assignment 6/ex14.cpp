#include <iostream>
#include <vector>
using namespace std;

bool isSortedRec(const vector<int>& arr, int i) {
    if (i >= (int)arr.size() - 1) return true;
    if (arr[i] > arr[i + 1]) return false;
    return isSortedRec(arr, i + 1);
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << (isSortedRec(arr, 0) ? "Sorted" : "Not sorted");
    return 0;
}
