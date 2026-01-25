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

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < n; j++) {
                array[i][j] = num++;
            }
        } else {
            for (int j = n - 1; j >= 0; j--) {
                array[i][j] = num++;
            }
        }
    }

    print_2d_array(array);
    return 0;
}
