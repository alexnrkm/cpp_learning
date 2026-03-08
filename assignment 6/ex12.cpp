#include <iostream>
#include <vector>
using namespace std;

int arrayLength(const vector<int>& arr, int index) {
    if (index == (int)arr.size()) return 0;
    return 1 + arrayLength(arr, index + 1);
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << "Length = " << arrayLength(arr, 0);
    return 0;
}
