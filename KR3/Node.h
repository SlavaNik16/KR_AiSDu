#ifndef NODE_H
#define NODE_H

// класс "узел дерева"
class Node {
private:
    char tag;           // метка узла
    Node* left;         // левый сын
    Node* right;        // правый сын

public:
    Node() : tag('?'), left(nullptr), right(nullptr) {}
    Node(char t) : tag(t), left(nullptr), right(nullptr) {}
    ~Node() {
        if (left) delete left;
        if (right) delete right;
    }

    friend class Tree; 
};

#endif