#include <iostream>
#include <vector>

using namespace std;


void print_2d_array(const vector<vector<int>>& arr) {
    int num_rows = arr.size();
    int num_columns = arr[0].size();
    for (int row = 0; row < num_rows; row++) {
        for (int column = 0; column < num_columns; column++) {
            cout << arr[row][column];
        }
        cout << "\n";
    }
}

int main() {
    int size;
    cout << "Enter the size of the matrix (3..99): ";
    cin >> size;

    if (size < 3 || size > 99) {
        cout << "Size must be between 3 and 99." << endl;
        return 0;
    }


    vector<vector<int>> array(size, vector<int>(size, 0));


    for (int row = 0; row < size; row++) {
        for (int column = 0; column < size; column++) {
            if (row == column || row + column == size - 1) {
                array[row][column] = 1;
            }
        }
    }


    print_2d_array(array);

    return 0;
}
