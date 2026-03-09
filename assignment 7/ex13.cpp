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

    vector<pair<K, V>> items() const {
        vector<pair<K, V>> result;
        for (Node* head : buckets) {
            Node* current = head;
            while (current != nullptr) {
                result.push_back(make_pair(current->key, current->value));
                current = current->next;
            }
        }
        return result;
    }
};

bool areAnagrams(const string& first, const string& second) {
    if (first.length() != second.length()) {
        return false;
    }

    HashTable<char, int> counts;
    for (char ch : first) {
        counts.insert(ch, counts.getOrDefault(ch, 0) + 1);
    }
    for (char ch : second) {
        counts.insert(ch, counts.getOrDefault(ch, 0) - 1);
    }

    vector<pair<char, int>> items = counts.items();
    for (const auto& item : items) {
        if (item.second != 0) {
            return false;
        }
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

    cout << "Anagrams: " << (areAnagrams(first, second) ? "true" : "false") << '\n';
    return 0;
}
