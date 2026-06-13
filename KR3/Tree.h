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

    // рекурсивная расстановка узлов на экране
    void placeNodes(Node* v, int row, int col);

    // внутренний обход (симметричный) - левый, узел, правый
    void inorderTraversal(Node* v, vector<char>& result);

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

    // создание дерева
    void makeTree();

    // проверка: дерево не пусто
    bool exists() const;

    // вывод дерева на экран
    void outTree();

    // внутренний обход (возвращает последовательность меток)
    vector<char> inorder();

    // вывод последовательности обхода
    void printInorder();

    // вычисление количества вершин на самом нижнем уровне
    int getBottomLevelCount();

    // ширинная разметка (вывод меток по уровням)
    void printLevelOrder();
};

#endif