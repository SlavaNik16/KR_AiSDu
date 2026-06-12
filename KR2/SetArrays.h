#ifndef SET_ARRAYS_H
#define SET_ARRAYS_H

#include <iostream>
#include <cstring>
#include "Utils.h"  
using namespace std;

class Set {
private:
    char* data;
    int size;
    static int counter;


    bool contains(char ch) const {
        for (int i = 0; i < size; i++) {
            if (data[i] == ch) return true;
        }
        return false;
    }

    void addChar(char ch) {
        if (!contains(ch) && charToIndex(ch) != -1 && size < ALPHABET_SIZE) {
            data[size++] = ch;
        }
    }

public:
    Set() : size(0), data(new char[ALPHABET_SIZE + 1]) {
        data[0] = '\0';
        counter++;
    }

    Set(const char* str) : size(0), data(new char[ALPHABET_SIZE + 1]) {
        data[0] = '\0';
        counter++;
        for (int i = 0; str[i]; i++) {
            addChar(str[i]);
        }
        data[size] = '\0';
    }

    Set(const Set& other) : size(other.size), data(new char[ALPHABET_SIZE + 1]) {
        strcpy_s(data, ALPHABET_SIZE + 1, other.data);
        counter++;
    }

    ~Set() {
        delete[] data;
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            size = other.size;
            strcpy_s(data, ALPHABET_SIZE + 1, other.data);
        }
        return *this;
    }

    Set operator&(const Set& other) const {
        Set result;
        for (int i = 0; i < size; i++) {
            if (other.contains(data[i]) && result.size < ALPHABET_SIZE) {
                result.data[result.size++] = data[i];
            }
        }
        result.data[result.size] = '\0';
        return result;
    }

    Set operator-(const Set& other) const {
        Set result;
        for (int i = 0; i < size; i++) {
            if (!other.contains(data[i]) && result.size < ALPHABET_SIZE) {
                result.data[result.size++] = data[i];
            }
        }
        result.data[result.size] = '\0';
        return result;
    }

    void generateRandom(int k) {
        size = 0;
        if (k > ALPHABET_SIZE) k = ALPHABET_SIZE;

        int indices[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) indices[i] = i;

        for (int i = 0; i < k; i++) {
            int p = rand() % (ALPHABET_SIZE - i);
            if (p != 0) swap(indices[i], indices[i + p]);
        }

        for (int i = 0; i < k; i++) {
            data[size++] = indexToChar(indices[i]);
        }
        data[size] = '\0';
    }

    void print(const char* name = nullptr) const {
        if (name) cout << name << " = ";
        cout << "{ ";
        if (size == 0) cout << " ";
        else {
            for (int i = 0; i < size; i++) {
                cout << data[i];
                if (i < size - 1) cout << ", ";
            }
        }
        cout << " }" << endl;
    }
};

int Set::counter = 0;

#endif