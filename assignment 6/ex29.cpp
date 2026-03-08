#include <iostream>
#include <vector>
#include <string>
using namespace std;

void solveQueens(int n, int row, vector<int>& col, vector<int>& d1, vector<int>& d2, vector<string>& board, vector<vector<string>>& ans) {
    if (row == n) {
        ans.push_back(board);
        return;
    }
    for (int c = 0; c < n; c++) {
        if (col[c] || d1[row - c + n - 1] || d2[row + c]) continue;
        col[c] = d1[row - c + n - 1] = d2[row + c] = 1;
        board[row][c] = 'Q';
        solveQueens(n, row + 1, col, d1, d2, board, ans);
        board[row][c] = '.';
        col[c] = d1[row - c + n - 1] = d2[row + c] = 0;
    }
}

int main() {
    int n;
    cout << "Enter N for N-Queens: ";
    cin >> n;
    vector<int> col(n, 0), d1(2 * n - 1, 0), d2(2 * n - 1, 0);
    vector<string> board(n, string(n, '.'));
    vector<vector<string>> ans;
    solveQueens(n, 0, col, d1, d2, board, ans);
    if (ans.empty()) {
        cout << "No solution";
    } else {
        cout << "Solutions:" << endl;
        for (auto solution : ans) {
            for (string row : solution) cout << row << endl;
            cout << endl;
        }
    }
    return 0;
}
