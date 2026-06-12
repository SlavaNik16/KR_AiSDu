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
    //int tag;  // уникальный тег для каждого объекта

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

    static int getCounter() {
        return counter;
    }

    // конструктор по умолчанию
    Set() : size(0), data(new char[ALPHABET_SIZE + 1]) {
        data[0] = '\0';
        counter++;
        //tag = counter;
        //cout << "[ДЕБАГ] Конструктор по умолчанию: Set" << tag << " создан (активных: " << counter << ")" << endl;
    }

    // конструктор из строки
    Set(const char* str) : size(0), data(new char[ALPHABET_SIZE + 1]) {
        data[0] = '\0';
        counter++;
        //tag = counter;
        //cout << "[ДЕБАГ] Конструктор из строки: Set" << tag << " создан из \"" << str << "\" (активных: " << counter << ")" << endl;
        for (int i = 0; str[i]; i++) {
            addChar(str[i]);
        }
        data[size] = '\0';
        //cout << "[ДЕБАГ]   -> содержимое Set" << tag << ": { ";
        //for (int i = 0; i < size; i++) cout << data[i] << " ";
        //cout << "}" << endl;
    }

    // конструктор копирования
    Set(const Set& other) : size(other.size), data(new char[ALPHABET_SIZE + 1]) {
        strcpy_s(data, ALPHABET_SIZE + 1, other.data);
        counter++;
        //tag = counter;
        //cout << "[ДЕБАГ] Конструктор копирования: Set" << tag << " скопирован из Set" << other.tag << " (активных: " << counter << ")" << endl;
    }

    // деструктор
    ~Set() {
        //cout << "[ДЕБАГ] Деструктор: Set" << tag << " уничтожен (активных осталось: " << counter - 1 << ")" << endl;
        delete[] data;
        counter--;
    }

    // оператор присваивания
    Set& operator=(const Set& other) {
        if (this != &other) {
            //cout << "[ДЕБАГ] Оператор присваивания: Set" << tag << " = Set" << other.tag << endl;
            size = other.size;
            strcpy_s(data, ALPHABET_SIZE + 1, other.data);
        }
        else {
            //cout << "[ДЕБАГ] Оператор присваивания: самоприсваивание Set" << tag << endl;
        }
        return *this;
    }

    // пересечение
    Set operator&(const Set& other) const {
        //cout << "[ДЕБАГ] Оператор &: Set" << tag << " & Set" << other.tag << endl;
        Set result;
        for (int i = 0; i < size; i++) {
            if (other.contains(data[i]) && result.size < ALPHABET_SIZE) {
                result.data[result.size++] = data[i];
            }
        }
        result.data[result.size] = '\0';
        //cout << "[ДЕБАГ]   -> результат: Set" << result.tag << " = { ";
        //for (int i = 0; i < result.size; i++) cout << result.data[i] << " ";
        //cout << "}" << endl;
        return result;
    }

    // разность
    Set operator-(const Set& other) const {
        //cout << "[ДЕБАГ] Оператор -: Set" << tag << " - Set" << other.tag << endl;
        Set result;
        for (int i = 0; i < size; i++) {
            if (!other.contains(data[i]) && result.size < ALPHABET_SIZE) {
                result.data[result.size++] = data[i];
            }
        }
        result.data[result.size] = '\0';
        //cout << "[ДЕБАГ]   -> результат: Set" << result.tag << " = { ";
        //for (int i = 0; i < result.size; i++) cout << result.data[i] << " ";
        //cout << "}" << endl;
        return result;
    }

    void generateRandom(int k) {
        //cout << "[ДЕБАГ] generateRandom: Set" << tag << " заполняется " << k << " элементами" << endl;
        size = 0;
        if (k > ALPHABET_SIZE) k = ALPHABET_SIZE;

        int indices[ALPHABET_SIZE];
        fisherYatesShuffle(indices, ALPHABET_SIZE, k);

        for (int i = 0; i < k; i++) {
            data[size++] = indexToChar(indices[i]);
        }
        data[size] = '\0';
        //cout << "[ДЕБАГ]   -> содержимое Set" << tag << ": { ";
        //for (int i = 0; i < size; i++) cout << data[i] << " ";
        //cout << "}" << endl;
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