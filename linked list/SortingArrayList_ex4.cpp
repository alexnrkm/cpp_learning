#include <iostream>
using namespace std;

void swap(double &a, double &b);
void bubble_sort(double array[], int size);

class ArrayList{
    private:
        int capacity = 0; //сколько элементов находится в массиве
        int array_size = 0; // размер всего массива
        double* array = new double[array_size];
    public:
       int add(double value);
       double get(int index);
       int get_size(void);
       void sort();
};

int ArrayList::add(double value){
    if (capacity == array_size){
        int new_size = (array_size == 0) ? 1: array_size * 2;
        double* new_array = new double[new_size];
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

double ArrayList::get(int index){
    if(index < 0 || index >= capacity){
        cout << "ERROR: index is out of an array size";
        return 1;
    }
    double output = array[index];
    return output;
}

int ArrayList:: get_size(void){
    return capacity;
}

void ArrayList::sort(){
    bubble_sort(array, capacity - 1);
}




int main(){
    ArrayList arr;
    double numbers[] = {1.01, 2.124, 1.524, 5.241, 4.124};
    for(int i{}; i < 5; i++){
        arr.add(numbers[i]);
    }

    for (int i{}; i < arr.get_size(); i++){
        cout << arr.get(i) << " ";
    }

    cout << endl << endl;

    arr.sort();

    for (int i{}; i < arr.get_size(); i++){
        cout << arr.get(i) << " ";
    }

    return 0;
}




void swap(double &a, double &b){
    double temp;
    temp = a;
    a = b;
    b = temp;
}

void bubble_sort(double array[], int size){
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