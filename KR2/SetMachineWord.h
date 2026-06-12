#ifndef SET_MACHINEWORD_H
#define SET_MACHINEWORD_H

#include <iostream>
#include <cstring>
#include "Utils.h"   // ← подключаем общий файл
using namespace std;

class Set {
private:
    unsigned long long word;
    int power;

public:
    Set() : word(0), power(0) {}

    Set(const char* str) : Set() {
        if (str == nullptr) return;
        for (size_t i = 0; i < strlen(str) && i < 80; i++) {
            int idx = charToIndex(str[i]);
            if (idx != -1 && !((word >> idx) & 1ULL)) {
                word |= (1ULL << idx);
                power++;
            }
        }
    }

    Set(const Set& other) : word(other.word), power(other.power) {}

    Set& operator=(const Set& other) {
        if (this != &other) {
            word = other.word;
            power = other.power;
        }
        return *this;
    }

    Set operator&(const Set& other) const {
        Set result;
        result.word = word & other.word;
        result.power = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if ((result.word >> i) & 1ULL) result.power++;
        }
        return result;
    }

    Set operator-(const Set& other) const {
        Set result;
        result.word = word & ~other.word;
        result.power = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if ((result.word >> i) & 1ULL) result.power++;
        }
        return result;
    }

    void generateRandom(int k) {
        word = 0;
        power = 0;

        if (k > ALPHABET_SIZE) k = ALPHABET_SIZE;

        int indices[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) indices[i] = i;

        for (int i = 0; i < k; i++) {
            int p = rand() % (ALPHABET_SIZE - i);
            if (p != 0) swap(indices[i], indices[i + p]);
        }

        for (int i = 0; i < k; i++) {
            word |= (1ULL << indices[i]);
            power++;
        }
    }

    void print(const char* name = nullptr) const {
        if (name) cout << name << " = ";
        cout << "{ ";
        if (power == 0) cout << " ";
        else {
            bool first = true;
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if ((word >> i) & 1ULL) {
                    if (!first) cout << ", ";
                    cout << indexToChar(i);
                    first = false;
                }
            }
        }
        cout << " }" << endl;
    }
};

#endif