#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void displayArray(int arr[][100], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << "\t";
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

void sortQuadrants(int arr[][100], int n) {
    if (n % 2 != 0) {
        cout << "\nMatrix size must be even for quadrant sorting.\n";
        return;
    }
    
    int mid = n / 2;
    int quadrant[2500];
    
    // Process each of the 4 quadrants
    for (int q = 0; q < 4; q++) {
        int startRow = (q < 2) ? 0 : mid;
        int endRow = (q < 2) ? mid : n;
        int startCol = (q % 2 == 0) ? 0 : mid;
        int endCol = (q % 2 == 0) ? mid : n;
        
        int index = 0;
        
        // Extract quadrant elements
        for (int i = startRow; i < endRow; i++) {
            for (int j = startCol; j < endCol; j++) {
                quadrant[index++] = arr[i][j];
            }
        }
        
        int quadSize = index;
        
        // Insertion sort (ascending order)
        for (int i = 1; i < quadSize; i++) {
            int key = quadrant[i];
            int j = i - 1;
            
            while (j >= 0 && quadrant[j] > key) {
                quadrant[j + 1] = quadrant[j];
                j--;
            }
            quadrant[j + 1] = key;
        }
        
        // Insert sorted elements back
        index = 0;
        for (int i = startRow; i < endRow; i++) {
            for (int j = startCol; j < endCol; j++) {
                arr[i][j] = quadrant[index++];
            }
        }
    }
}

int main() {
    srand(time(0));
    
    int n;
    int arr[100][100];
    
    cout << "Enter the size of square matrix (must be even): ";
    cin >> n;
    
    fillRandomMatrix(arr, n);
    
    cout << "\nOriginal Matrix:\n";
    displayArray(arr, n);
    
    sortQuadrants(arr, n);
    
    cout << "\nMatrix after Quadrant-wise Sorting:\n";
    displayArray(arr, n);
    cout << "\n(Each quadrant sorted independently in ascending order)\n";
    
    return 0;
}