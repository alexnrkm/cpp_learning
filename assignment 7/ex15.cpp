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

vector<int> findAllAnagrams(const string& text, const string& pattern) {
    vector<int> indices;
    if (pattern.empty() || text.length() < pattern.length()) {
        return indices;
    }

    HashTable<char, int> targetCount;
    HashTable<char, int> windowCount;
    for (char ch : pattern) {
        targetCount.insert(ch, targetCount.getOrDefault(ch, 0) + 1);
    }

    vector<pair<char, int>> targetItems = targetCount.items();
    int matchedKinds = 0;
    int requiredKinds = static_cast<int>(targetItems.size());

    for (size_t right = 0; right < text.length(); ++right) {
        char incoming = text[right];
        if (targetCount.contains(incoming)) {
            int newValue = windowCount.getOrDefault(incoming, 0) + 1;
            windowCount.insert(incoming, newValue);

            int targetValue = targetCount.getOrDefault(incoming, 0);
            if (newValue == targetValue) {
                ++matchedKinds;
            } else if (newValue == targetValue + 1) {
                --matchedKinds;
            }
        }

        if (right >= pattern.length()) {
            char outgoing = text[right - pattern.length()];
            if (targetCount.contains(outgoing)) {
                int currentValue = windowCount.getOrDefault(outgoing, 0);
                int targetValue = targetCount.getOrDefault(outgoing, 0);
                if (currentValue == targetValue) {
                    --matchedKinds;
                } else if (currentValue == targetValue + 1) {
                    ++matchedKinds;
                }
                windowCount.insert(outgoing, currentValue - 1);
            }
        }

        if (right + 1 >= pattern.length() && matchedKinds == requiredKinds) {
            indices.push_back(static_cast<int>(right + 1 - pattern.length()));
        }
    }

    return indices;
}

int main() {
    string text;
    string pattern;

    cout << "Enter the main string without spaces: ";
    cin >> text;
    cout << "Enter the pattern string without spaces: ";
    cin >> pattern;

    vector<int> indices = findAllAnagrams(text, pattern);
    cout << "Starting indices: [";
    for (size_t i = 0; i < indices.size(); ++i) {
        cout << indices[i];
        if (i + 1 != indices.size()) {
            cout << ", ";
        }
    }
    cout << "]\n";

    return 0;
}
