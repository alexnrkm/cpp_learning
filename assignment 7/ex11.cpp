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

bool hasZeroSumSubarray(const vector<int>& numbers) {
    HashTable<int, bool> prefixSums;
    prefixSums.insert(0, true);

    int prefix = 0;
    for (int number : numbers) {
        prefix += number;
        if (prefixSums.contains(prefix)) {
            return true;
        }
        prefixSums.insert(prefix, true);
    }

    return false;
}

int main() {
    int n;
    cout << "Enter the number of integers: ";
    cin >> n;

    vector<int> numbers(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << "Contains a zero-sum subarray: " << (hasZeroSumSubarray(numbers) ? "true" : "false") << '\n';
    return 0;
}
