#include "hash_functions.hpp"
#include <cmath>

namespace HashFunctions {

    int hashModulo(int key, int tableSize) {
        return key % tableSize;
    }

    int hashMultiplication(int key, int tableSize) {
        const double A = 0.6180339887; // (sqrt(5) - 1)/2
        double frac = (key * A) - static_cast<int>(key * A);
        return static_cast<int>(tableSize * frac);
    }

    int hashXOR(int key, int tableSize) {
        return (key ^ (key >> 3)) % tableSize;
    }

    int hashLinear(int key, int tableSize) {
        const int a = 31;
        const int b = 7;
        return (a * key + b) % tableSize;
    }

}

