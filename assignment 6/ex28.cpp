#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dr[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool inside(int n, int r, int c) {
    return r >= 0 && c >= 0 && r < n && c < n;
}

int degree(const vector<vector<int>>& board, int r, int c) {
    int n = board.size();
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (inside(n, nr, nc) && board[nr][nc] == -1) cnt++;
    }
    return cnt;
}

bool knightTour(vector<vector<int>>& board, int r, int c, int moveNo) {
    int n = board.size();
    if (moveNo == n * n) return true;
    vector<pair<int, pair<int, int>>> nextMoves;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (inside(n, nr, nc) && board[nr][nc] == -1) {
            nextMoves.push_back({degree(board, nr, nc), {nr, nc}});
        }
    }
    sort(nextMoves.begin(), nextMoves.end());
    for (auto move : nextMoves) {
        int nr = move.second.first;
        int nc = move.second.second;
        board[nr][nc] = moveNo;
        if (knightTour(board, nr, nc, moveNo + 1)) return true;
        board[nr][nc] = -1;
    }
    return false;
}

int main() {
    int n;
    cout << "Enter board size N: ";
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, -1));
    board[0][0] = 0;
    if (knightTour(board, 0, 0, 1)) {
        cout << "Knight's tour:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << board[i][j] + 1 << " ";
            cout << endl;
        }
    } else {
        cout << "No solution";
    }
    return 0;
}
