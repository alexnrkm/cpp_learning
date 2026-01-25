#include <iostream>
#include <vector>
using namespace std;

void print_2d_array(const vector<vector<int>>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n;
    cin >> n;
    if (n < 5 || n > 99) return 0;

    vector<vector<int>> array(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int top = i;
            int left = j;
            int bottom = n - 1 - i;
            int right = n - 1 - j;
            int min_dist = min(min(top, bottom), min(left, right));
            array[i][j] = min_dist + 1;
        }
    }

    print_2d_array(array);
    return 0;
}
