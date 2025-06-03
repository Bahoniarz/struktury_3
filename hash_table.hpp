#ifndef HASH_TABLE_HPP_
#define HASH_TABLE_HPP_

class HashTable {
protected:
    int tableSize;      ///< Liczba kube�k�w (m)
    int elementCount;   ///< Liczba element�w (n)

public:
    ///  Konstruktor bazowy
    //size Rozmiar tablicy haszuj�cej
    HashTable(int size) : tableSize(size), elementCount(0) {}

    // Wirtualny destruktor
    virtual ~HashTable() {}

    ///  Wstawienie elementu do tablicy
    virtual void insert(int key) = 0;

    /// Usuni�cie elementu z tablicy
    virtual void remove(int key) = 0;

    ///  Wyszukanie elementu w tablicy
    virtual bool find(int key) = 0;

    /// Zwraca aktualny wsp�czynnik zaj�to�ci (= n / m)
    double load_factor() const {
        return static_cast<double>(elementCount) / tableSize;
    }

    /// Zwraca liczb� element�w w tablicy
    int size() const {
        return elementCount;
    }

    ///  Zwraca rozmiar tablicy (liczb� kube�k�w)
    int capacity() const {
        return tableSize;
    }
};

#endif 
