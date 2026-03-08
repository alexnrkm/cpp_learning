#include <iostream>
#include <vector>
using namespace std;

int findMinRec(const vector<int>& arr, int n) {
    if (n == 1) return arr[0];
    int m = findMinRec(arr, n - 1);
    return arr[n - 1] < m ? arr[n - 1] : m;
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << "Minimum = " << findMinRec(arr, n);
    return 0;
}
