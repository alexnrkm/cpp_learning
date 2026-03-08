#include <iostream>
#include <vector>
using namespace std;

bool isValid(vector<vector<int>>& board, int r, int c, int num) {
    for (int i = 0; i < 9; i++) {
        if (board[r][i] == num || board[i][c] == num) return false;
    }
    int sr = (r / 3) * 3;
    int sc = (c / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[sr + i][sc + j] == num) return false;
        }
    }
    return true;
}

bool solveSudoku(vector<vector<int>>& board, int cell) {
    if (cell == 81) return true;
    int r = cell / 9;
    int c = cell % 9;
    if (board[r][c] != 0) return solveSudoku(board, cell + 1);
    for (int num = 1; num <= 9; num++) {
        if (isValid(board, r, c, num)) {
            board[r][c] = num;
            if (solveSudoku(board, cell + 1)) return true;
            board[r][c] = 0;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> board(9, vector<int>(9));
    cout << "Enter 9x9 Sudoku grid, use 0 for empty cells:" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) cin >> board[i][j];
    }
    if (solveSudoku(board, 0)) {
        cout << "Solved Sudoku:" << endl;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) cout << board[i][j] << " ";
            cout << endl;
        }
    } else {
        cout << "No solution";
    }
    return 0;
}
