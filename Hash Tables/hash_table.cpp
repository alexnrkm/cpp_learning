//Implementing hash table logic on my own
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

class HashTable{
    private: // private are the things that only functions inside the class can use and user cannot access it.
        static const int hashGroups =  10; //declaring the size of the hash table. ('static' - allows to share this variable, not copies of it) ('const' - cannot change)
        list<pair<int, string>> table[hashGroups]; //declaring a paired list called table (size of hashGroup). Paired list = (2 items on the list)
    
    public:
        bool isEmpty() const; // this const means that the function cannot modify the object, in simple words it's read only
        int hashFunction(int key);
        void insertItem (int key, string value);
        void removeItem (int key);
        string searchTable (int key);
        void printTable ();
};


//function that returns true if the whole list is empty
bool HashTable::isEmpty() const {
    int sum{}; //int sum = 0
    for (int i{}; i < hashGroups; i++){
        sum += table[i].size();
    }
    if (!sum){
        return true;
    }
    return false;
}

// returns the hash value of the key
int HashTable::hashFunction(int key) {
    return key % hashGroups;
}

void HashTable::insertItem(int key, string value) {
    int hash_value = hashFunction(key);
    auto &cell = table[hash_value]; //it’s a reference to the whole number of lists in the bucket. We use & to be able to modify the variable that it points to, not creating a copy. If we try to modify without & it will modify a copy but not the original variable that we are working with
    auto iterable = begin(cell); // iterable is pointing to the first key-value pair in that bucket.
    bool  key_exists = false;
    // for every pair in the list check if the key already exist, insert if doesn't, replace if the key already exist
    for (iterable; iterable != end(cell); iterable++){ // here iterable++ just follows the next pointer to the next node of the linked list
        if (iterable->first == key){
            key_exists = true;
            iterable->second = value;
            cout << "The key already exists and the value was replaced" << "\n";
            break;
        }
    }
    if (!key_exists){
        cell.push_back({key, value});
    }
    return;
}

 string HashTable::searchTable (int key){
    int hash_value = hashFunction(key);
    auto &cell = table[hash_value];
    auto iterable = begin(cell);

    for (iterable; iterable != end(cell); iterable++){
        if (iterable->first == key){
            return iterable->second;
            break;
        }
    }
    cout << "[ERROR] The key " << key << " wasn't found" << endl;
    return "";

 }

void HashTable::removeItem(int key) {
    int hash_value = hashFunction(key);
    auto &cell = table[hash_value];
    auto iterable = begin(cell);
    
    for (iterable; iterable != end(cell); iterable++){
        if (iterable->first == key){
            cell.erase(iterable);
            cout << "Key " << key << " removed successfully" << endl;
            return;
        }
    }
    cout << "Key " << key << " not found" << endl;
}

void HashTable::printTable() {
    for (int i = 0; i < hashGroups; i++){
        cout << "Index " << i << ":"; 
        for (auto x : table[i]){
            cout << " [" << x.first << ", " << x.second << "]";
        }
        cout << endl;
    }
}

 int main(){
    HashTable ht;
    int num_of_lists;
    cout << "type the number of linked list you want to enter: ";
    cin >> num_of_lists;

    for (int i{}; i < num_of_lists; i++){
        cout << "The " << i+1 << "st Key: ";
        int key;
        cin >> key;
        cout << "The " << i+1 << "st Value: ";
        string value;
        cin >> value;

        if (typeid(value) != typeid(string)){
            cout << "Only string values are allowed";
            return 1;
        }
        
        ht.insertItem(key, value);
    }

    int key_input;
    cout << "type the key you want to search: ";
    cin >> key_input;

    string search_output = ht.searchTable(key_input);
    cout << search_output;

 }