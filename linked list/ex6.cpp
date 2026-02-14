#include <iostream>
using namespace std;

void bubble_sort(int array[], int size);

class ArrayList{
    private:
        int capacity = 0; //сколько элементов находится в массиве
        int array_size = 0; // размер всего массива
        int* array = new int[array_size];
    public:
       int add(int value);
       int get(int index);
       int get_size(void);
       auto reverse();
       void remove(int index);
       void sort();
       void remove_duplicates();
};

int ArrayList::add(int value){
    if (capacity == array_size){
        int new_size = (array_size == 0) ? 1: array_size * 2;
        int* new_array = new int[new_size];
        for (int i{}; i < array_size; i++){
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        array_size = new_size;
    }
    array[capacity] = value;
    capacity++;
    return capacity;
}

int ArrayList::get(int index){
    if(index < 0 || index >= capacity){
        cout << "ERROR: index is out of an array size";
        return 1;
    }
    int output = array[index];
    return output;
}

int ArrayList:: get_size(void){
    return capacity;
}

auto ArrayList::reverse(){
    int* new_array = new int[array_size];
    int counter{};
    for (int i = capacity - 1; i >= 0; i--){
        new_array[counter] = array[i];
        counter++;
    }
    return new_array; 
}

void ArrayList::sort(){
    bubble_sort(array, capacity - 1);
}

void ArrayList::remove(int index){
    if (index < 0 || index >= capacity){ // проверить если индекс входит в границы списка
        cout << "Invalid index";
        return;
    }
    for (int i = index; i < capacity - 1; i++){ // передвигаем направо все элементы которые стоят после удаляемого элемента
        array[i] = array[i+1];
    }
    array[capacity - 1] = 0;
    capacity--;
}

void ArrayList::remove_duplicates(){
    for (int target{}; target < capacity; target++){
        for (int current{}; current < capacity; current++){
            if (array[current] == array[target] && current!=target){
                remove(current);
            }
        }
    }
}



int main(){
    ArrayList arr_list;
    int values[9] = {10, 20, 30, 40, 50, 20, 15, 20, 30};

    for (int i{}; i < 9; i++){
        arr_list.add(values[i]);
    }

    int size = arr_list.get_size();

    cout << "Original Array: "<< endl;
    for (int i{}; i < size; i++){
        int output = arr_list.get(i);
        cout << output << endl;
    }

    cout << "\n \n";

    arr_list.remove_duplicates();

    size = arr_list.get_size();

    cout << "Array with removed dublicates: "<< endl;
    for (int i{}; i < size; i++){
        int output = arr_list.get(i);
        cout << output << endl;
    }


    return 0;
}


void bubble_sort(int array[], int size){
    int swap_count = 1;
    while (swap_count != 0){
        swap_count = 0;
        for (int i{}; i < size; i++){
            if(array[i] > array[i+1]){
                swap(array[i], array[i+1]);
                swap_count++;
            }
        }
    }

}

