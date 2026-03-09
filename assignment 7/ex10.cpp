#include <algorithm>
#include <functional>
#include <iostream>
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

vector<int> intersection(const vector<int>& first, const vector<int>& second) {
    HashTable<int, bool> fromFirst;
    HashTable<int, bool> added;
    vector<int> result;

    for (int value : first) {
        fromFirst.insert(value, true);
    }

    for (int value : second) {
        if (fromFirst.contains(value) && !added.contains(value)) {
            result.push_back(value);
            added.insert(value, true);
        }
    }

    sort(result.begin(), result.end());
    return result;
}

int main() {
    int n1;
    cout << "Enter the size of the first array: ";
    cin >> n1;
    vector<int> first(n1);
    cout << "Enter " << n1 << " integers for the first array: ";
    for (int i = 0; i < n1; ++i) {
        cin >> first[i];
    }

    int n2;
    cout << "Enter the size of the second array: ";
    cin >> n2;
    vector<int> second(n2);
    cout << "Enter " << n2 << " integers for the second array: ";
    for (int i = 0; i < n2; ++i) {
        cin >> second[i];
    }

    vector<int> result = intersection(first, second);
    cout << "Intersection: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i + 1 != result.size()) {
            cout << ", ";
        }
    }
    cout << "]\n";

    return 0;
}
