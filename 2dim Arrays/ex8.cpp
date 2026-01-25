#include <iostream>
#include <vector>
using namespace std;

void print_2d_array(const vector<vector<int>>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            cout << arr[i][j];
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cin >> n;
    if (n < 3 || n > 99) return 0;

    vector<vector<int>> array(n, vector<int>(n, 0));

    int mid = n / 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < mid && j < mid) array[i][j] = 1;
            else if (i < mid && j > mid) array[i][j] = 2;
            else if (i > mid && j < mid) array[i][j] = 3;
            else if (i > mid && j > mid) array[i][j] = 4;
        }
    }

    print_2d_array(array);
    return 0;
}
