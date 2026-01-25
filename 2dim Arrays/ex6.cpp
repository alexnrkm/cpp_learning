#include <iostream>
#include <vector>

using namespace std;

void print_2d_array(const vector<vector<int>>& arr) {
    for (int row = 0; row < arr.size(); row++) {
        for (int col = 0; col < arr[row].size(); col++) {
            cout << arr[row][col] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cin >> n;
    if (n < 5 || n > 99) return 0;

    vector<vector<int>> array(n, vector<int>(n));

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            array[row][col] = row + col + 1;
        }
    }

    print_2d_array(array);
    return 0;
}
