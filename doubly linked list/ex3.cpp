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
        void SortedInsert(T value);
        void PrintForward();
        void PrintBackward();
        void RemoveDuplicates();

};

template <typename T>
void DLinkedList<T>::SortedInsert(T value){
    Node<T>* new_node = new Node<T>(value);

    if (Head == nullptr){
        Head = Tail = new_node;
    }
    else if(value <= Head->value){
        new_node->next = Head;
        Head->prev = new_node;
        Head = new_node;
    }
    else if(value >= Tail->value){
        Tail->next = new_node;
        new_node->prev = Tail;
        Tail = new_node;
    }
    else{
        Node<T>* current = Head;

        while (current->next!=nullptr){
            Node<T>* next_node = current->next;

            if (value >= current->value && value < next_node->value){
                new_node->prev = current;
                new_node->next = next_node;

                current->next = new_node;
                next_node->prev = new_node;

                break;
            }
            current = current->next;
        }
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

template <typename T>
void DLinkedList<T>::RemoveDuplicates(){
    Node<T>* current = Head;
    while(current->next!=nullptr){
        Node<T>* next_node = current->next;

        if(current->value == next_node->value){
            Node<T>* over_next_node = next_node->next;
            if(over_next_node == nullptr){
                current->next = nullptr;
                Tail = current;
                delete next_node;
            }
            else{
                current->next = over_next_node;
                over_next_node->prev = current;
                delete next_node;
            }
        }
        if(current->value != next_node->value){
            current=current->next;
        }

    }
}


int main(){
    DLinkedList<int> list;
    int value;

    for (int i{}; i < 10; i++){
        cout << "Enter a value: ";
        cin >> value;
        list.SortedInsert(value);
    }

    list.PrintForward();

    list.RemoveDuplicates();
    cout << "\n \n";

    list.PrintForward();

    return 0;
}