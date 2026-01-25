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
    if (n < 8 || n > 99 || n % 2 != 0) return 0;

    vector<vector<int>> array(n, vector<int>(n, 0));
    int half = n / 2;
    int quarter = n / 4;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < half && j < quarter) array[i][j] = 1;
            else if (i < half && j < half) array[i][j] = 2;
            else if (i < half && j < 3*quarter) array[i][j] = 4;
            else if (i < half) array[i][j] = 1;

            else if (i < n && j < quarter) array[i][j] = 2;
            else if (i < n && j < half) array[i][j] = 1;
            else if (i < n && j < 3*quarter) array[i][j] = 1;
            else array[i][j] = 4;
        }
    }

    print_2d_array(array);
    return 0;
}
