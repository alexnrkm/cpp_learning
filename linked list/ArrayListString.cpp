#include <iostream>
#include <string>
using namespace std;

class ArrayListString{
    private:
        int size = 0; // размер массива
        int capacity = 0; // сколько элементов находится в массиве
        string *array = new string[size];

    public:
        void add(string word);
        void remove(int index);
        string get(int index);
        int get_size(void);
};

void ArrayListString::add(string word){
    // Задаем новый размер массива, копируем старый массив с новый
    if (capacity == size){
        int new_size = (size == 0) ? 1: size * 2;
        string *new_array = new string[new_size];
        for (int i{}; i < size; i++){
            new_array[i] = array[i];
        }
    // Освобождаем оригинальный массив, ставим указатель что оригинальный массив теперь указывает на новый
        delete[] array;
        array = new_array;
        size = new_size;
    }
    array[capacity] = word;
    capacity++;
}

void ArrayListString::remove(int index){
    if (index < 0 || index >= capacity){ // проверить если индекс входит в границы списка
        cout << "Invalid index";
        return;
    }
    for (int i = index; i < capacity - 1; i++){ // передвигаем направо все элементы которые стоят после удаляемого элемента
        array[i] = array[i+1];
    }
    array[capacity - 1] = "";
    capacity--;
}

string ArrayListString::get(int index){
    if (index < 0 || index >= capacity){
        cout << "Invalid index";
        return "";
    }

    string output = array[index];
    return output;
}

int ArrayListString::get_size(void){
    return capacity;
}

int main(){
    string words[5] = {"Alexander", "Bogdan", "Nurlan", "Arlan", "Sati"};
    ArrayListString array;

    for (int i{}; i < 5; i++){
        array.add(words[i]);
    }

    cout << "words were added to the list: ";

    int size = array.get_size();

    for (int i{}; i < size; i++){
        string word = array.get(i);
        cout << word << " ";
    }

    array.remove(2);
    cout << endl << "item with index 2 was removed" << endl;

    size = array.get_size();

    for (int i{}; i < size; i++){
        string word = array.get(i);
        cout << word << " ";
    }

    return 0;
}