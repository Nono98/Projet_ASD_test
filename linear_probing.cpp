#include <vector>
#include <string>
#include <iostream>

template<typename T>
class LinearProbing {
private:
    size_t m;
    size_t n;
    std::vector<T> hashTable;

public:

    LinearProbing(size_t capacity) {
        m = capacity;
        n = 0;
        hashTable.reserve(capacity);
        hashTable.assign(capacity, T());
    }

    int size() {
        return n;
    }

    size_t hash(T key) {
        return (31 * 17 + (std::hash<T>()(key))) % m;
    }

    bool contains(T key) {
        for (size_t i = 0; i < m; ++i) {
            if (hashTable[i] == key) {
                return true;
            }
        }
        return false;
    }

    void insert(T key) {

        // double the size of the tab
        if (double(n / m) >= 0.5){
            m *= 2;
            hashTable.reserve(m);
            hashTable.resize(m, T());
        }

        size_t i;
        for (i = hash(key); hashTable[i] != 0; i = (i + 1) % m) {
            // if the c is already in the table, we don't insert it
            if (hashTable[i] == key) {
                return;
            }
        }
        hashTable[i] = key;
        ++n;
    }

    void erase(T key) {

        if (!contains(key)) return;

        // find position of c
        size_t i = hash(key);
        while (key != hashTable[i]) {
            i = (i + 1) % m;
        }

        //delete the c
        hashTable[i] = T();

        // rehash all the table
        i = (i + 1) % m;
        while (hashTable[i] != 0) {
            T temp = hashTable[i];
            hashTable[i] = T();
            n--;
            insert(temp);
            i = (i + 1) % m;
        }
        n--;

        // reduce size
        if (double(n / m) <= 0.125){
            m /= 2;
            hashTable.resize(m);
        }

    }

};

inline bool operator ==(const std::string& op1, const int& op2){
    return op1 == std::to_string(op2);
}

inline bool operator !=(const std::string& op1, const int& op2) {
    return (op1 != "");
}
