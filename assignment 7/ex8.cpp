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

bool canBeFormedByTwoWords(const vector<string>& words, const string& target) {
    HashTable<string, int> frequencies;
    for (const string& word : words) {
        frequencies.insert(word, frequencies.getOrDefault(word, 0) + 1);
    }

    for (size_t i = 1; i < target.length(); ++i) {
        string left = target.substr(0, i);
        string right = target.substr(i);

        if (!frequencies.contains(left) || !frequencies.contains(right)) {
            continue;
        }

        if (left != right || frequencies.getOrDefault(left, 0) >= 2) {
            return true;
        }
    }

    return false;
}

int main() {
    int n;
    cout << "Enter the number of dictionary words: ";
    cin >> n;

    vector<string> words(n);
    cout << "Enter " << n << " words: ";
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    string target;
    cout << "Enter the target word: ";
    cin >> target;

    cout << "Can be formed by concatenating two words: "
         << (canBeFormedByTwoWords(words, target) ? "true" : "false") << '\n';
    return 0;
}
