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

int mostFrequentElement(const vector<int>& numbers) {
    HashTable<int, int> frequencies;
    int bestValue = numbers[0];
    int bestFrequency = 0;

    for (int number : numbers) {
        int frequency = frequencies.getOrDefault(number, 0) + 1;
        frequencies.insert(number, frequency);
        if (frequency > bestFrequency) {
            bestFrequency = frequency;
            bestValue = number;
        }
    }

    return bestValue;
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

    cout << "Most frequent element: " << mostFrequentElement(numbers) << '\n';
    return 0;
}
