#include "hash_table_chaining.hpp"
#include <algorithm>
#include <iostream>

void HashTableChaining::insert(int key) {
    int index = hashFunction(key, tableSize);
    auto& bucket = table[index];

    // SprawdŸ, czy klucz ju¿ istnieje (nie dodawaj duplikatów)
    if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
        bucket.push_back(key);
        elementCount++;
    }
}

void HashTableChaining::remove(int key) {
    int index = hashFunction(key, tableSize);
    auto& bucket = table[index];

    auto it = std::find(bucket.begin(), bucket.end(), key);
    if (it != bucket.end()) {
        bucket.erase(it);
        elementCount--;
    }
}

bool HashTableChaining::find(int key) {
    int index = hashFunction(key, tableSize);
    auto& bucket = table[index];

    return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
}
