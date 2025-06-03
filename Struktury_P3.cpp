#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <algorithm>

#include "hash_table_chaining.hpp"
#include "hash_table_open.hpp"
#include "hash_table_cuckoo.hpp"
#include "hash_functions.hpp"

using namespace std;
using Clock = chrono::high_resolution_clock;

// Generowanie danych (unikalne klucze)
vector<int> generateOptimistic(int n) {
    vector<int> data;
    for (int i = 1; i <= n; ++i) data.push_back(i); // Dane idealnie rozproszone
    return data;
}

vector<int> generateAverage(int n) {
    vector<int> data = generateOptimistic(n);
    shuffle(data.begin(), data.end(), default_random_engine(42)); // Tasowanie
    return data;
}

vector<int> generatePessimistic(int n, int modValue) {
    vector<int> data;
    for (int i = 0; i < n; ++i) data.push_back(i * modValue); // Wielokrotności modValue powodują kolizje
    return data;
}

// Pomiar czasu dla 1 testu
template <typename TableType>
pair<double, double> singleTest(TableType& table, const vector<int>& data) {
    auto start = Clock::now();
    for (int key : data) table.insert(key);
    auto end = Clock::now();
    chrono::duration<double, milli> insertTime = end - start;  

    start = Clock::now();
    for (int key : data) table.remove(key);
    end = Clock::now();
    chrono::duration<double, milli> removeTime = end - start;  

    return { insertTime.count(), removeTime.count() };
}


template <typename TableType>
pair<double, double> benchmark(TableType& table, const vector<int>& data) {
    const int trials = 50;
    double totalInsert = 0;
    double totalRemove = 0;

    for (int i = 0; i < trials; ++i) {
        TableType tempTable = table; 
        auto times = singleTest(tempTable, data);
        totalInsert += times.first;
        totalRemove += times.second;
    }

    return { totalInsert / trials, totalRemove / trials };
}

int main() {
    const int tableSize = 10007;
    vector<int> sizes = { 1000, 2000, 4000, 8000 };

    ofstream out("nowewyniki.csv");
    out << "Struktura,Algorytm,Przypadek,n,Sredni_czas_insert(ms),Sredni_czas_remove(ms)\n";  

    vector<pair<string, int(*)(int, int)>> hashFunctions = {
        {"Modulo", HashFunctions::hashModulo},
        {"Mnozenie", HashFunctions::hashMultiplication},
        {"XOR", HashFunctions::hashXOR},
        {"Linear", HashFunctions::hashLinear}
    };

    for (auto& hf : hashFunctions) {
        string hashName = hf.first;
        auto hashFunc = hf.second;

        for (int n : sizes) {
            // Dane testowe
            auto dataOpt = generateOptimistic(n);
            auto dataAvg = generateAverage(n);
            auto dataPes = generatePessimistic(n, tableSize / 2);
            

            vector<pair<string, vector<int>>> cases = {
                //{"Optymistyczny", dataOpt},
                //{"Sredni", dataAvg},
                {"Pesymistyczny", dataPes}
            };

            for (auto& testCase : cases) {
                string caseName = testCase.first;
                vector<int>& data = testCase.second;

                if ((caseName != "Chaining") && (n > tableSize)) {
                    cout << "[Pominieto] " << caseName << " | " << hashName << " | n=" << n << " (n > tableSize)" << endl;
                    continue;
                }

                // Chaining
                {
                    HashTableChaining table(tableSize, hashFunc);
                    auto avgTimes = benchmark(table, data);
                    out << "Chaining," << hashName << "," << caseName << "," << n << "," << avgTimes.first << "," << avgTimes.second << "\n";
                    cout << "Chaining | " << hashName << " | " << caseName << " | n=" << n
                        << " | insert avg: " << avgTimes.first << " ms"
                        << " | remove avg: " << avgTimes.second << " ms\n";
                }

                // Open Addressing
                if (n <= tableSize) {
                    HashTableOpen table(tableSize, hashFunc);
                    auto avgTimes = benchmark(table, data);
                    out << "Open," << hashName << "," << caseName << "," << n << "," << avgTimes.first << "," << avgTimes.second << "\n";
                    cout << "Open | " << hashName << " | " << caseName << " | n=" << n
                        << " | insert avg: " << avgTimes.first << " ms"
                        << " | remove avg: " << avgTimes.second << " ms\n";
                }
                else {
                    cout << "[Pominieto] Open | " << hashName << " | " << caseName << " | n=" << n << " (n > tableSize)" << endl;
                }

                // Cuckoo Hashing
                if (n <= tableSize) {
                    HashTableCuckoo table(tableSize, hashFunc, HashFunctions::hashMultiplication);
                    auto avgTimes = benchmark(table, data);
                    out << "Cuckoo," << hashName << "," << caseName << "," << n << "," << avgTimes.first << "," << avgTimes.second << "\n";
                    cout << "Cuckoo | " << hashName << " | " << caseName << " | n=" << n
                        << " | insert avg: " << avgTimes.first << " ms"
                        << " | remove avg: " << avgTimes.second << " ms\n";
                }
                else {
                    cout << "[Pominieto] Cuckoo | " << hashName << " | " << caseName << " | n=" << n << " (n > tableSize)" << endl;
                }

                cout << hashName << " | " << caseName << " | n=" << n << " zapisane\n";
            }
        }
    }

    out.close();
    cout << "\nTesty zakonczone. Dane zapisano w pliku nowewyniki.csv.\n";
    return 0;
}
