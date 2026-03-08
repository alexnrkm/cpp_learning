#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool searchWord(vector<string>& board, string& word, int r, int c, int index) {
    if (index == (int)word.size()) return true;
    if (r < 0 || c < 0 || r >= (int)board.size() || c >= (int)board[0].size()) return false;
    if (board[r][c] != word[index]) return false;

    char temp = board[r][c];
    board[r][c] = '#';
    bool found = searchWord(board, word, r + 1, c, index + 1) ||
                 searchWord(board, word, r - 1, c, index + 1) ||
                 searchWord(board, word, r, c + 1, index + 1) ||
                 searchWord(board, word, r, c - 1, index + 1);
    board[r][c] = temp;
    return found;
}

int main() {
    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    vector<string> board(rows);
    cout << "Enter the board rows:" << endl;
    for (int i = 0; i < rows; i++) cin >> board[i];
    string word;
    cout << "Enter the word to search: ";
    cin >> word;
    bool found = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (searchWord(board, word, i, j, 0)) found = true;
        }
    }
    cout << (found ? "Word found" : "Word not found");
    return 0;
}
