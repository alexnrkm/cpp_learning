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

vector<int> commonElements(const vector<int>& first, const vector<int>& second, const vector<int>& third) {
    HashTable<int, bool> inFirst;
    HashTable<int, bool> inSecond;
    HashTable<int, bool> added;
    vector<int> result;

    for (int value : first) {
        inFirst.insert(value, true);
    }
    for (int value : second) {
        inSecond.insert(value, true);
    }

    for (int value : third) {
        if (inFirst.contains(value) && inSecond.contains(value) && !added.contains(value)) {
            result.push_back(value);
            added.insert(value, true);
        }
    }

    sort(result.begin(), result.end());
    return result;
}

int main() {
    int n1;
    cout << "Enter the size of the first sorted array: ";
    cin >> n1;
    vector<int> first(n1);
    cout << "Enter " << n1 << " integers for the first array: ";
    for (int i = 0; i < n1; ++i) {
        cin >> first[i];
    }

    int n2;
    cout << "Enter the size of the second sorted array: ";
    cin >> n2;
    vector<int> second(n2);
    cout << "Enter " << n2 << " integers for the second array: ";
    for (int i = 0; i < n2; ++i) {
        cin >> second[i];
    }

    int n3;
    cout << "Enter the size of the third sorted array: ";
    cin >> n3;
    vector<int> third(n3);
    cout << "Enter " << n3 << " integers for the third array: ";
    for (int i = 0; i < n3; ++i) {
        cin >> third[i];
    }

    vector<int> result = commonElements(first, second, third);
    cout << "Common elements: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i + 1 != result.size()) {
            cout << ", ";
        }
    }
    cout << "]\n";

    return 0;
}
