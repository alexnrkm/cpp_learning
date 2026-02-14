#include <iostream>
using namespace std;

template <typename T>
class Node{
    public: 
        T value;
        Node<T>* next = nullptr;
        Node<T>* prev = nullptr;
    
        Node(T val) : value(val) {} //Its a constructor which means assign value to val
};

template <typename T>
class DLinkedList{
    private: 
        Node<T>* Head = nullptr;
        Node<T>* Tail = nullptr;
        int size = 0;

    public:
        void AddEnd(T value);
        void PrintForward();
        void PrintBackward();

};

template <typename T>
void DLinkedList<T>::AddEnd(T value){
    Node<T>* new_node = new Node<T>(value);

    if (Head == nullptr){
        Head = Tail = new_node;
    }
    else{
        new_node->prev = Tail;
        Tail->next = new_node;
        Tail = new_node;
    }
    size++;
}

template <typename T>
void DLinkedList<T>::PrintForward(){
    Node<T>* current = Head;
    while(current!=nullptr){
        cout << current->value << " ";
        current = current->next;
    }
}


template <typename T>
void DLinkedList<T>::PrintBackward(){
    Node<T>* current = Tail;
    while (current!=nullptr){
        cout << current->value << " ";
        current = current->prev;
    }
}


int main(){
    DLinkedList<int> list;
    int value;

    for (int i{}; i < 10; i++){
        cout << "Enter a value: ";
        cin >> value;
        list.AddEnd(value);
    }

    list.PrintForward();

    cout << "\n \n";

    list.PrintBackward();

    return 0;
}