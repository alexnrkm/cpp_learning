#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string>

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

    int *sorted_array = new int[num_of_values];
    for (int i{}; i < num_of_values; i++){
        sorted_array[i] = i;
    }

    int *worst_case_array = new int[num_of_values];
    for (int i{}; i < num_of_values; i++){
        sorted_array[i] = num_of_values - i;
    }

    string array_names[3] = {"random_array", "sorted_array", "worst_case_array"};
    int *names[3] = {array, sorted_array, worst_case_array};

    for (int i = 0; i < 3; i++){
        auto start_time = chrono::steady_clock::now(); // measuring the start of the algorithm
        int s_num;
        for (int j{}; j < num_of_values; j++){
            s_num = find_smallest_index(names[i], num_of_values);
            swap(s_num, j, names[i], num_of_values);
        }
        auto end_time = chrono::steady_clock::now();
        auto time_elapsed = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cout << endl << array_names[i] << " time elapsed: " << time_elapsed.count() << " miliseconds" << endl;
    }

    delete[] array, sorted_array, worst_case_array; //освободить память

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