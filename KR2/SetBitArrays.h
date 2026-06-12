#ifndef SET_BITARRAYS_H
#define SET_BITARRAYS_H

#include <iostream>
#include <cstring>
#include "Utils.h"   // ← подключаем общий файл
using namespace std;

class Set {
private:
    bool bits[ALPHABET_SIZE];
    int power;

public:
    Set() : power(0) {
        for (int i = 0; i < ALPHABET_SIZE; i++) bits[i] = false;
    }

    Set(const char* str) : Set() {
        for (int i = 0; str[i]; i++) {
            int idx = charToIndex(str[i]);
            if (idx != -1 && !bits[idx]) {
                bits[idx] = true;
                power++;
            }
        }
    }

    Set(const Set& other) : power(other.power) {
        for (int i = 0; i < ALPHABET_SIZE; i++) bits[i] = other.bits[i];
    }

    Set operator&(const Set& other) const {
        Set result;
        result.power = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            result.bits[i] = bits[i] && other.bits[i];
            if (result.bits[i]) result.power++;
        }
        return result;
    }

    Set operator-(const Set& other) const {
        Set result;
        result.power = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            result.bits[i] = bits[i] && !other.bits[i];
            if (result.bits[i]) result.power++;
        }
        return result;
    }

    void generateRandom(int k) {
        power = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) bits[i] = false;

        if (k > ALPHABET_SIZE) k = ALPHABET_SIZE;

        int indices[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) indices[i] = i;

        for (int i = 0; i < k; i++) {
            int p = rand() % (ALPHABET_SIZE - i);
            if (p != 0) swap(indices[i], indices[i + p]);
        }

        for (int i = 0; i < k; i++) {
            bits[indices[i]] = true;
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
                if (bits[i]) {
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