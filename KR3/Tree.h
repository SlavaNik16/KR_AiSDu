#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <queue>
#include <vector>
#include "Node.h"
using namespace std;

// класс "дерево"
class Tree {
private:
    Node* root;           // указатель на корень
    char currentTag;      // текущая метка для разметки
    char maxTag;          // максимальная метка
    int maxDepth;         // максимальная глубина для вывода
    int offset;           // смещение корня при выводе
    char** screen;        // буфер для вывода на экран
    int bottomLevelCount; // количество вершин на самом нижнем уровне
    int maxLevel;         // максимальный уровень (глубина) дерева

    // очистка экранного буфера
    void clearScreen();

    // рекурсивное создание дерева (ширинная разметка)
    Node* makeNode(int depth, int& levelCount);

    // рекурсивное создание дерева (ширинная разметка) (ручной ввод)
    Node* makeNodeManual(int depth, int& levelCount);

    // рекурсивная расстановка узлов на экране
    void placeNodes(Node* v, int row, int col);

    // внутренний обход (симметричный) - левый, узел, правый
    void inorderTraversal(Node* v, vector<char>& result);

    // прямой - узел, левый, правый
    void preorderTraversal(Node* v, vector<char>& result);

    // обратный - левый, правый, узел
    void postorderTraversal(Node* v, vector<char>& result);

    // обход для подсчёта количества узлов на самом нижнем уровне
    void countBottomLevel(Node* v, int depth);

    // отключённые конструкторы (делаем невозможными)
    Tree(const Tree&) {}
    Tree(Tree&&) {}
    Tree& operator=(const Tree&) { return *this; }
    Tree& operator=(Tree&&) { return *this; }

public:
    // конструктор
    Tree(char startTag, char endTag, int maxDepth);

    // деструктор
    ~Tree();

    // создание дерева (случайная генерация)
    void makeTree();

    // создание дерева (ручной ввод с клавиатуры)
    void makeTreeManual();

    // проверка: дерево не пусто
    bool exists() const;

    // вывод дерева на экран
    void outTree();

    // внутренний обход - левый, узел, правый
    vector<char> inorder();
    void printInorder();

    // прямой обход - узел, левый, правый
    vector<char> preorder();
    void printPreorder();

    // обратный обход - левый, правый, узел
    vector<char> postorder();
    void printPostorder();

    // вычисление количества вершин на самом нижнем уровне
    int getBottomLevelCount();

    // обход в ширину с выводом по уровням
    void printBFSLevels();

    // обход в глубину с выводом по уровням
    void printDFSLevels();

    // обход в ширину одной строкой
    void printBFS();

    // обход в глубину одной строкой
    void printDFS();  
};

#endif