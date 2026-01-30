#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void displayArray(int arr[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void fillRandomMatrix(int arr[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % 100 + 1;
        }
    }
}

void sortInnerCore(int arr[][100], int n) {
    if (n <= 2) {
        cout << "\nMatrix size must be greater than 2 for inner core sorting.\n";
        return;
    }
    
    int inner[10000];
    int index = 0;
    
    // Extract inner elements
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            inner[index++] = arr[i][j];
        }
    }
    
    int totalInner = index;
    
    cout << "\nInner elements (before sorting): ";
    for (int i = 0; i < totalInner; i++) {
        cout << inner[i] << " ";
    }
    cout << endl;
    
    // Selection sort (descending order)
    for (int i = 0; i < totalInner - 1; i++) {
        int maxIdx = i;
        
        for (int j = i + 1; j < totalInner; j++) {
            if (inner[j] > inner[maxIdx]) {
                maxIdx = j;
            }
        }
        
        if (maxIdx != i) {
            int temp = inner[i];
            inner[i] = inner[maxIdx];
            inner[maxIdx] = temp;
        }
    }
    
    cout << "Inner elements (after sorting): ";
    for (int i = 0; i < totalInner; i++) {
        cout << inner[i] << " ";
    }
    cout << endl;
    
    // Insert sorted elements back
    index = 0;
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            arr[i][j] = inner[index++];
        }
    }
}

int main() {
    srand(time(0));
    
    int n;
    int arr[100][100];
    
    cout << "Enter the size of square matrix (N > 2): ";
    cin >> n;
    
    fillRandomMatrix(arr, n);
    
    cout << "\nOriginal Matrix:\n";
    displayArray(arr, n);
    
    sortInnerCore(arr, n);
    
    cout << "\nMatrix after Inner-Core Sorting:\n";
    displayArray(arr, n);
    
    return 0;
}