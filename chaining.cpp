#include <vector>
#include <iostream>

template<typename T>
class Chaining {
private:
    size_t m;
    size_t n;
    std::vector<std::vector<T>> hashTable;

public:

    Chaining(): Chaining(1) {}
    Chaining(size_t capacity) {
        m = capacity;
        n = 0;
        hashTable.resize(capacity);

        for(size_t i = 0; i < capacity; ++i){
            hashTable.at(i).resize(capacity);
        }
    }

    size_t size() {
        return n;
    }

    size_t hash(T key) {
        return (31 * 17 + (std::hash<T>()(key))) % m;
    }

    bool contains(T key) {
        int index = hash(key);
        // we are directly searching in the correct index
        for (size_t i = 0; i < hashTable.at(index).size(); ++i) {
            if (hashTable.at(index).at(i) == key) {
                return true;
            }
        }
        return false;
    }

    void insert(T key) {
        if (double(n / m) >= 8) resize();
        int index = hash(key);
        for (size_t i = 0; i < hashTable.at(index).size(); ++i) {
            // if key is already in the table, we don't insert it
            if (hashTable.at(index).at(i) == key) {
                return;
            }
        }
        hashTable.at(index).push_back(key);
        ++n;
    }

    void erase(T key) {

        if (!contains(key)) return;

        //find position of key
        size_t index = hash(key);
        size_t j = 0;
        while (key != hashTable.at(index).at(j)) {
            ++j;
        }

        // if the key to erase is the first element of the table
        if(hashTable.at(index).size() == 1)
            hashTable.at(index).erase(hashTable.at(index).begin());

            // if it is the last element of the table
        else if(j + 1 == hashTable.at(index).size())
            hashTable.at(index).erase(hashTable.at(index).begin() + j);

            // else
        else
            for (; j + 1 < hashTable.at(index).size(); ++j)
                hashTable.at(index).at(j) = hashTable.at(index).at(j + 1);

        --n;
        // reduce size
        if (double(n / m) <= 2) resize();
    }

    void resize(){
        size_t oldM = m;
        std::vector<std::vector<T>> tmp = hashTable;

        // double the size
        if (double(n / m) >= 8) {
            m *= 2;
            hashTable.clear();
            hashTable.resize(m);
            for (size_t i = 0; i < m; ++i) {
                hashTable.at(i).resize(m);
            }
        }

            // reduce size by two
        else {
            m /= 2;
            hashTable.clear();
            hashTable.resize(m);
            for (size_t i = 0; i < m; ++i) {
                hashTable.at(i).resize(m);
            }
        }
        // rehash all the keys with the new capacity (m)
        for (size_t i = 0; i < oldM; ++i) {
            for (size_t j = 0; j < tmp.at(i).size(); ++j) {
                --n;
                insert(tmp.at(i).at(j));
            }
        }
    }
};

