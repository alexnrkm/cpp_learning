#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void displayArray(int arr[][100], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

void fillRandomMatrix(int arr[][100], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % 100 + 1;
        }
    }
}

void sortZigZagColumns(int arr[][100], int rows, int cols) {
    for (int j = 0; j < cols; j++) {
        // Bubble sort for each column
        for (int i = 0; i < rows - 1; i++) {
            for (int k = 0; k < rows - i - 1; k++) {
                bool shouldSwap = false;
                
                if (j % 2 == 0) {
                    // Even-indexed column: descending order
                    if (arr[k][j] < arr[k + 1][j]) {
                        shouldSwap = true;
                    }
                } else {
                    // Odd-indexed column: ascending order
                    if (arr[k][j] > arr[k + 1][j]) {
                        shouldSwap = true;
                    }
                }
                
                if (shouldSwap) {
                    int temp = arr[k][j];
                    arr[k][j] = arr[k + 1][j];
                    arr[k + 1][j] = temp;
                }
            }
        }
    }
}

int main() {
    srand(time(0));
    
    int rows, cols;
    int arr[100][100];
    
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    
    fillRandomMatrix(arr, rows, cols);
    
    cout << "\nOriginal Matrix:\n";
    displayArray(arr, rows, cols);
    
    sortZigZagColumns(arr, rows, cols);
    
    cout << "\nMatrix after Zig-Zag Column Sorting:\n";
    displayArray(arr, rows, cols);
    cout << "\n(Even columns descending, Odd columns ascending)\n";
    
    return 0;
}