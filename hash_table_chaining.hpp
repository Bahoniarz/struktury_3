#ifndef HASH_TABLE_CHAINING_HPP_
#define HASH_TABLE_CHAINING_HPP_

#include "hash_table.hpp"
#include <vector>
#include <list>

class HashTableChaining : public HashTable {
private:
    std::vector<std::list<int>> table;

    // Wskaünik do funkcji haszujπcej
    int (*hashFunction)(int key, int tableSize);

public:
    
    HashTableChaining(int size, int (*hashFunc)(int, int))
        : HashTable(size), table(size), hashFunction(hashFunc) {
    }


    void insert(int key) override;


    void remove(int key) override;

    bool find(int key) override;
};

#endif
