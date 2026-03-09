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

char firstNonRepeatingCharacter(const string& text) {
    HashTable<char, int> frequencies;

    for (char ch : text) {
        frequencies.insert(ch, frequencies.getOrDefault(ch, 0) + 1);
    }

    for (char ch : text) {
        if (frequencies.getOrDefault(ch, 0) == 1) {
            return ch;
        }
    }

    return '\0';
}

int main() {
    string text;
    cout << "Enter a string without spaces: ";
    cin >> text;

    char result = firstNonRepeatingCharacter(text);
    if (result == '\0') {
        cout << "First non-repeating character: none\n";
    } else {
        cout << "First non-repeating character: " << result << '\n';
    }

    return 0;
}
