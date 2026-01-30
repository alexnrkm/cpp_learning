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

void sortColumnsByRange(int arr[][100], int rows, int cols) {
    int ranges[100];
    int tempCol[100];
    
    // Calculate range for each column
    for (int j = 0; j < cols; j++) {
        int minVal = arr[0][j];
        int maxVal = arr[0][j];
        
        for (int i = 1; i < rows; i++) {
            if (arr[i][j] < minVal) {
                minVal = arr[i][j];
            }
            if (arr[i][j] > maxVal) {
                maxVal = arr[i][j];
            }
        }
        
        ranges[j] = maxVal - minVal;
    }
    
    cout << "\nColumn Ranges: ";
    for (int j = 0; j < cols; j++) {
        cout << ranges[j] << " ";
    }
    cout << endl;
    
    // Insertion sort on columns based on range (ascending order)
    for (int i = 1; i < cols; i++) {
        int keyRange = ranges[i];
        
        // Store column i in temporary array
        for (int k = 0; k < rows; k++) {
            tempCol[k] = arr[k][i];
        }
        
        int j = i - 1;
        
        // Shift columns with larger ranges to the right
        while (j >= 0 && ranges[j] > keyRange) {
            ranges[j + 1] = ranges[j];
            for (int k = 0; k < rows; k++) {
                arr[k][j + 1] = arr[k][j];
            }
            j--;
        }
        
        // Insert the stored column
        ranges[j + 1] = keyRange;
        for (int k = 0; k < rows; k++) {
            arr[k][j + 1] = tempCol[k];
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
    
    sortColumnsByRange(arr, rows, cols);
    
    cout << "\nMatrix after sorting columns by range:\n";
    displayArray(arr, rows, cols);
    
    return 0;
}