#ifndef SET_LISTS_H
#define SET_LISTS_H

#include <iostream>
#include <cstring>
#include "Utils.h" 
using namespace std;

struct Node {
    char val;
    Node* next;
    Node(char v, Node* n = nullptr) : val(v), next(n) {}
};

class Set {
private:
    Node* head;
    int power;

    bool inList(char ch) const {
        for (Node* p = head; p; p = p->next) {
            if (p->val == ch) return true;
        }
        return false;
    }

    void addToList(char ch) {
        if (!inList(ch)) {
            head = new Node(ch, head);
            power++;
        }
    }

public:
    Set() : head(nullptr), power(0) {}

    Set(const char* str) : head(nullptr), power(0) {
        for (int i = 0; str[i]; i++) {
            addToList(str[i]);
        }
    }

    Set(const Set& other) : head(nullptr), power(0) {
        Node* prev = nullptr;
        for (Node* p = other.head; p; p = p->next) {
            Node* newNode = new Node(p->val);
            if (!head) head = newNode;
            if (prev) prev->next = newNode;
            prev = newNode;
            power++;
        }
    }

    ~Set() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            while (head) {
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
            power = 0;

            Node* prev = nullptr;
            for (Node* p = other.head; p; p = p->next) {
                Node* newNode = new Node(p->val);
                if (!head) head = newNode;
                if (prev) prev->next = newNode;
                prev = newNode;
                power++;
            }
        }
        return *this;
    }

    Set operator&(const Set& other) const {
        Set result;
        for (Node* p = head; p; p = p->next) {
            if (other.inList(p->val)) {
                result.addToList(p->val);
            }
        }
        return result;
    }

    Set operator-(const Set& other) const {
        Set result;
        for (Node* p = head; p; p = p->next) {
            if (!other.inList(p->val)) {
                result.addToList(p->val);
            }
        }
        return result;
    }

    void generateRandom(int k) {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        power = 0;
        if (k > ALPHABET_SIZE) k = ALPHABET_SIZE;

        int indices[ALPHABET_SIZE];
        fisherYatesShuffle(indices, ALPHABET_SIZE, k);

        for (int i = k - 1; i >= 0; i--) {
            head = new Node(indexToChar(indices[i]), head);
            power++;
        }
    }

    void print(const char* name = nullptr) const {
        if (name) cout << name << " = ";
        cout << "{ ";
        if (power == 0) cout << " ";
        else {
            Node* p = head;
            while (p) {
                cout << p->val;
                if (p->next) cout << ", ";
                p = p->next;
            }
        }
        cout << " }" << endl;
    }
};

#endif