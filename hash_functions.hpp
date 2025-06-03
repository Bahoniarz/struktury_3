#ifndef HASH_FUNCTIONS_HPP_
#define HASH_FUNCTIONS_HPP_

#pragma once

namespace HashFunctions {
    int hashModulo(int key, int tableSize);
    int hashMultiplication(int key, int tableSize);
    int hashXOR(int key, int tableSize);
    int hashLinear(int key, int tableSize); // Nowa funkcja
}


#endif