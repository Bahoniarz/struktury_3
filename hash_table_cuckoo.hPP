#ifndef HASH_TABLE_CUCKOO_HPP
#define HASH_TABLE_CUCKOO_HPP

#pragma once
#include "hash_table.hpp"
#include <vector>
#include <iostream>

class HashTableCuckoo : public HashTable {
private:
    std::vector<int> table1;
    std::vector<int> table2;
    int (*hashFunc1)(int key, int tableSize);
    int (*hashFunc2)(int key, int tableSize);
    const int MAX_RELOCATIONS = 10; // Maksymalna liczba przerzuceñ, aby unikn¹æ cyklu

public:
    HashTableCuckoo(int size, int (*h1)(int, int), int (*h2)(int, int))
        : HashTable(size), table1(size, 0), table2(size, 0),
        hashFunc1(h1), hashFunc2(h2) {
    }

    void insert(int key) override;
    void remove(int key) override;
    bool find(int key) override;
};



#endif