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
    if (n < 3 || n > 101) return 0;

    vector<vector<int>> array(n, vector<int>(n, 0));

    int num = 1;
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; j++) array[top][j] = num++;
        top++;
        for (int i = top; i <= bottom; i++) array[i][right] = num++;
        right--;
        if (top <= bottom) {
            for (int j = right; j >= left; j--) array[bottom][j] = num++;
            bottom--;
        }
        if (left <= right) {
            for (int i = bottom; i >= top; i--) array[i][left] = num++;
            left++;
        }
    }

    print_2d_array(array);
    return 0;
}
