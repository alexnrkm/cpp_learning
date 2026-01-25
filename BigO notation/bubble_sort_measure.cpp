#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>

using namespace std;

void swap(int a, int b, int * array, int size);


int main(){
    int num_of_values = 0;
    cout << "Enter the number of random values to sort: ";
    cin >> num_of_values;

    int *array = new int[num_of_values];
    for (int i{}; i < num_of_values; i++){
        srand(chrono::system_clock::now().time_since_epoch().count()); // устанавливает разный сид для rand
        array[i] = rand() % (i + 4); // генерирует случайное число между 0 и i+3;
    }
    cout << "The random array is generated" << endl << endl;

    auto start_time = chrono::steady_clock::now(); // measuring the start of the algorithm

    int swap_count = 1;
    cout << "sorting the array..." << endl;
    while (swap_count != 0)
    {
        swap_count = 0;
        for (int i{}; i < num_of_values - 1; i++){
            if (array[i] > array[i+1]){
                swap(i, i+1, array, num_of_values);
                swap_count = swap_count + 1;
            }
        }
    }
    auto end_time = chrono::steady_clock::now();

    cout << endl << "The array is sorted" << endl;

    auto time_elapsed = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << endl << "time elapsed: " << time_elapsed.count() << " miliseconds";

    delete[] array; //освободить память
    return 0;
}

void swap(int a, int b, int *array, int size){
    if (a >= size || b >= size){
        cout << "index cannot be more than size of the array";
        return;
    }

    int a_copy = array[a];
    array[a] = array[b];
    array[b] = a_copy;
}