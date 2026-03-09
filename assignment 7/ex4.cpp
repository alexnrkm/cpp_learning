#include <algorithm>
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

vector<pair<int, int>> findPairsWithSum(const vector<int>& numbers, int target) {
    HashTable<int, bool> seen;
    HashTable<string, bool> addedPairs;
    vector<pair<int, int>> pairs;

    for (int number : numbers) {
        int needed = target - number;
        if (seen.contains(needed)) {
            int left = min(number, needed);
            int right = max(number, needed);
            string key = to_string(left) + "#" + to_string(right);
            if (!addedPairs.contains(key)) {
                pairs.push_back(make_pair(left, right));
                addedPairs.insert(key, true);
            }
        }
        seen.insert(number, true);
    }

    sort(pairs.begin(), pairs.end());
    return pairs;
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

    int target;
    cout << "Enter the target sum: ";
    cin >> target;

    vector<pair<int, int>> pairs = findPairsWithSum(numbers, target);
    cout << "Pairs: [";
    for (size_t i = 0; i < pairs.size(); ++i) {
        cout << "(" << pairs[i].first << ", " << pairs[i].second << ")";
        if (i + 1 != pairs.size()) {
            cout << ", ";
        }
    }
    cout << "]\n";

    return 0;
}
