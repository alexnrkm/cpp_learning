#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename K, typename V>
class HashTable {
private:
    struct Node {
        K key;
        V value;
        Node* next;

        Node(const K& newKey, const V& newValue) : key(newKey), value(newValue), next(nullptr) {}
    };

    vector<Node*> buckets;

    size_t hashIndex(const K& key) const {
        return hash<K>{}(key) % buckets.size();
    }

public:
    explicit HashTable(size_t bucketCount = 211) : buckets(bucketCount, nullptr) {}

    ~HashTable() {
        clear();
    }

    void clear() {
        for (Node*& head : buckets) {
            while (head != nullptr) {
                Node* next = head->next;
                delete head;
                head = next;
            }
        }
    }

    bool contains(const K& key) const {
        size_t index = hashIndex(key);
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    V getOrDefault(const K& key, const V& defaultValue) const {
        size_t index = hashIndex(key);
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return defaultValue;
    }

    void insert(const K& key, const V& value) {
        size_t index = hashIndex(key);
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* node = new Node(key, value);
        node->next = buckets[index];
        buckets[index] = node;
    }
};

bool areIsomorphic(const string& first, const string& second) {
    if (first.length() != second.length()) {
        return false;
    }

    HashTable<char, char> leftToRight;
    HashTable<char, char> rightToLeft;

    for (size_t i = 0; i < first.length(); ++i) {
        char left = first[i];
        char right = second[i];

        if (leftToRight.contains(left) && leftToRight.getOrDefault(left, '\0') != right) {
            return false;
        }
        if (rightToLeft.contains(right) && rightToLeft.getOrDefault(right, '\0') != left) {
            return false;
        }

        leftToRight.insert(left, right);
        rightToLeft.insert(right, left);
    }

    return true;
}

int main() {
    string first;
    string second;

    cout << "Enter the first string without spaces: ";
    cin >> first;
    cout << "Enter the second string without spaces: ";
    cin >> second;

    cout << "Isomorphic: " << (areIsomorphic(first, second) ? "true" : "false") << '\n';
    return 0;
}
