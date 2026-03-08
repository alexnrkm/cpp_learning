#include <iostream>
#include <vector>
using namespace std;

int sumArray(const vector<int>& arr, int n) {
    if (n == 0) return 0;
    return arr[n - 1] + sumArray(arr, n - 1);
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << "Sum = " << sumArray(arr, n);
    return 0;
}
