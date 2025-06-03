#include "hash_table_cuckoo.hpp"

void HashTableCuckoo::insert(int key) {
    int currentKey = key;
    int tableIndex = 1;

    for (int i = 0; i < MAX_RELOCATIONS; ++i) {
        int pos;
        if (tableIndex == 1) {
            pos = hashFunc1(currentKey, tableSize);
            if (table1[pos] == 0) {
                table1[pos] = currentKey;
                elementCount++;
                return;
            }
            else {
                std::swap(currentKey, table1[pos]);
                tableIndex = 2;
            }
        }
        else {
            pos = hashFunc2(currentKey, tableSize);
            if (table2[pos] == 0) {
                table2[pos] = currentKey;
                elementCount++;
                return;
            }
            else {
                std::swap(currentKey, table2[pos]);
                tableIndex = 1;
            }
        }
    }

}

void HashTableCuckoo::remove(int key) {
    int pos1 = hashFunc1(key, tableSize);
    if (table1[pos1] == key) {
        table1[pos1] = 0;
        elementCount--;
        return;
    }

    int pos2 = hashFunc2(key, tableSize);
    if (table2[pos2] == key) {
        table2[pos2] = 0;
        elementCount--;
    }
}

bool HashTableCuckoo::find(int key) {
    int pos1 = hashFunc1(key, tableSize);
    if (table1[pos1] == key) return true;

    int pos2 = hashFunc2(key, tableSize);
    if (table2[pos2] == key) return true;

    return false;
}

