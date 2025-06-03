#ifndef HASH_TABBLE_OPEN_HPP_
#define HASH_TABBLE_OPEN_HPP_
#pragma once
#include "hash_table.hpp"
#include <vector>

class HashTableOpen : public HashTable {
private:
    struct Entry {
        int key;
        bool isDeleted;
        Entry() : key(0), isDeleted(false) {}
    };

    std::vector<Entry> table;
    int (*hashFunction)(int key, int tableSize);

    // Sta³a do linear probing (np. 1)
    static constexpr int C = 1;

public:
    HashTableOpen(int size, int (*hashFunc)(int, int))
        : HashTable(size), table(size), hashFunction(hashFunc) {
    }

    void insert(int key) override;
    void remove(int key) override;
    bool find(int key) override;
};






#endif