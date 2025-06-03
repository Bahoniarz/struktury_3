#ifndef HASH_TABLE_HPP_
#define HASH_TABLE_HPP_

class HashTable {
protected:
    int tableSize;      ///< Liczba kube³ków (m)
    int elementCount;   ///< Liczba elementów (n)

public:
    ///  Konstruktor bazowy
    //size Rozmiar tablicy haszuj¹cej
    HashTable(int size) : tableSize(size), elementCount(0) {}

    // Wirtualny destruktor
    virtual ~HashTable() {}

    ///  Wstawienie elementu do tablicy
    virtual void insert(int key) = 0;

    /// Usuniêcie elementu z tablicy
    virtual void remove(int key) = 0;

    ///  Wyszukanie elementu w tablicy
    virtual bool find(int key) = 0;

    /// Zwraca aktualny wspó³czynnik zajêtoœci (= n / m)
    double load_factor() const {
        return static_cast<double>(elementCount) / tableSize;
    }

    /// Zwraca liczbê elementów w tablicy
    int size() const {
        return elementCount;
    }

    ///  Zwraca rozmiar tablicy (liczbê kube³ków)
    int capacity() const {
        return tableSize;
    }
};

#endif 
