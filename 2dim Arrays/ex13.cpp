#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n, radius;
    cin >> n >> radius;

    if (n < 9 || n > 99 || radius < 1 || radius > n/2) return 0;

    vector<vector<char>> array(n, vector<char>(n, '#'));

    int cx = n / 2;
    int cy = n / 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int dx = j - cx;
            int dy = i - cy;
            if (sqrt(dx*dx + dy*dy) <= radius) {
                array[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << array[i][j];
        }
        cout << "\n";
    }

    return 0;
}
