#include <iostream>
#include <vector>
using namespace std;

bool solveMaze(vector<vector<int>>& maze, int r, int c, vector<pair<int, int>>& path, vector<vector<int>>& vis) {
    int n = maze.size();
    if (r < 0 || c < 0 || r >= n || c >= n) return false;
    if (maze[r][c] == 0 || vis[r][c]) return false;

    vis[r][c] = 1;
    path.push_back({r, c});
    if (r == n - 1 && c == n - 1) return true;

    if (solveMaze(maze, r + 1, c, path, vis) ||
        solveMaze(maze, r, c + 1, path, vis) ||
        solveMaze(maze, r - 1, c, path, vis) ||
        solveMaze(maze, r, c - 1, path, vis)) return true;

    path.pop_back();
    return false;
}

int main() {
    int n;
    cout << "Enter maze size N: ";
    cin >> n;
    vector<vector<int>> maze(n, vector<int>(n));
    cout << "Enter the maze values (0 or 1):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> maze[i][j];
    }
    vector<pair<int, int>> path;
    vector<vector<int>> vis(n, vector<int>(n, 0));
    if (solveMaze(maze, 0, 0, path, vis)) {
        cout << "Path:" << endl;
        for (auto p : path) cout << "(" << p.first << ", " << p.second << ")" << endl;
    } else {
        cout << "No path found";
    }
    return 0;
}
