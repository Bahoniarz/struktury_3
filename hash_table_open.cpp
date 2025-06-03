#include "hash_table_open.hpp"
#include <iostream>

void HashTableOpen::insert(int key) {
    int index = hashFunction(key, tableSize);
    int startIndex = index;
    int i = 0;

    while (true) {
        int probeIndex = (index + i * C) % tableSize;
        if (!table[probeIndex].isDeleted && table[probeIndex].key != 0) {
            i++;
            if (probeIndex == startIndex) {
               
                return;
            }
            continue;
        }
        else {
            table[probeIndex].key = key;
            table[probeIndex].isDeleted = false;
            elementCount++;
            return;
        }
    }
}

void HashTableOpen::remove(int key) {
    int index = hashFunction(key, tableSize);
    int i = 0;

    while (i < tableSize) {
        int probeIndex = (index + i * C) % tableSize;

        if (table[probeIndex].key == key && !table[probeIndex].isDeleted) {
            table[probeIndex].isDeleted = true;
            elementCount--;
            return;
        }
        else if (table[probeIndex].key == 0 && !table[probeIndex].isDeleted) {
            // Pusty kube³ek, elementu nie ma
            return;
        }
        i++;
    }
}

bool HashTableOpen::find(int key) {
    int index = hashFunction(key, tableSize);
    int i = 0;

    while (i < tableSize) {
        int probeIndex = (index + i * C) % tableSize;

        if (table[probeIndex].key == key && !table[probeIndex].isDeleted) {
            return true;
        }
        else if (table[probeIndex].key == 0 && !table[probeIndex].isDeleted) {
            return false;
        }
        i++;
    }
    return false;
}
