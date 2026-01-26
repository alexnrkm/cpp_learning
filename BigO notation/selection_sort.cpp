#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;

void swap(int a, int b, int * array, int size);
int find_smallest_index(int *array, int size);


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

    cout << "sorting the array..." << endl;
    int s_num;
    for (int i{}; i < num_of_values; i++){
        s_num = find_smallest_index(array, num_of_values);
        swap(s_num, i, array, num_of_values);
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

int find_smallest_index(int *array, int size){
    int smallest = size;
    for (int i{}; i < size; i++){   
        if (smallest > array[i]){
            smallest = i;
        }
    }
    return smallest;
}