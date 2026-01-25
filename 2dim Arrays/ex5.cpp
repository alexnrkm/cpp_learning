#include <iostream>
#include <vector>

using namespace std;

void print_2d_array(const vector<vector<int>>& arr) {
    for (int row = 0; row < arr.size(); row++) {
        for (int col = 0; col < arr[row].size(); col++) {
            cout << arr[row][col];
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cin >> n;
    if (n < 3 || n > 99) return 0;

    vector<vector<int>> array(n, vector<int>(n, 0));

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row == 0 || row == n-1 || col == 0 || col == n-1) {
                array[row][col] = 1;
            } else if ((row % 2 == col % 2) && row != n/2 && col != n/2) {
                array[row][col] = 1;
            } else if ((row == n/2 || col == n/2) && (row != 0 && row != n-1 && col != 0 && col != n-1)) {
                array[row][col] = 1;
            }
        }
    }

    print_2d_array(array);
    return 0;
}
