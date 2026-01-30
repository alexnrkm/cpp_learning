#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string>

using namespace std;

void swap(int a, int b, int * array, int size);


int main(){
    int num_of_values = 0;
    cout << "Enter the number of random values to sort: ";
    cin >> num_of_values;

    int *array = new int[num_of_values];
    for (int i{}; i < num_of_values; i++){
        srand(chrono::system_clock::now().time_since_epoch().count());
        array[i] = rand() % (i + 4);
    }

    int *sorted_array = new int[num_of_values];
    for (int i{}; i < num_of_values; i++){
        sorted_array[i] = i;
    }

    int *worst_case_array = new int[num_of_values];
    for (int i{}; i < num_of_values; i++){
        worst_case_array[i] = num_of_values - i;
    }

    string array_names[3] = {"random_array", "sorted_array", "worst_case_array"};
    int *names[3] = {array, sorted_array, worst_case_array};

    for (int i = 0; i < 3; i++){
        auto start_time = chrono::steady_clock::now();
        
        for (int j = 1; j < num_of_values; j++){
            int key = names[i][j];
            int k = j - 1;
            
            while (k >= 0 && names[i][k] > key){
                names[i][k + 1] = names[i][k];
                k--;
            }
            names[i][k + 1] = key;
        }
        
        auto end_time = chrono::steady_clock::now();
        auto time_elapsed = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cout << endl << array_names[i] << " time elapsed: " << time_elapsed.count() << " miliseconds" << endl;
    }

    delete[] array;
    delete[] sorted_array;
    delete[] worst_case_array;

    return 0;
}