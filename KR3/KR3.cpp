// ==================================================
// Лабораторная работа №3
// ==================================================
// Автор: Николаев Вячеслав Алексеевич
// Группа: 4335
// Вариант: 17
// Задача: Двоичное дерево, ширинная разметка,
//         внутренний обход, количество вершин на самом нижнем уровне
// Система: Visual Studio 2022 / C++17
// Дата: 6 июня 2026 г.
// ==================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Tree.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    cout << "------------------------------------------------------------" << endl;
    cout << "Лабораторная работа №3" << endl;
    cout << "Вариант 17: Двоичное дерево" << endl;
    cout << "  - Ширинная разметка" << endl;
    cout << "  - Внутренний обход" << endl;
    cout << "  - Количество вершин на самом нижнем уровне" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;

    Tree tree('a', 'z', 8);
    // Tree t2;                    // ошибка: нет конструктора по умолчанию
    // Tree t3 = tree;             // ошибка: копирование запрещено

    tree.makeTree();
    if (tree.exists()) {
        tree.outTree();
        tree.printLevelOrder();
        cout << endl;

        tree.printInorder();
        cout << endl;

        int bottomCount = tree.getBottomLevelCount();
        cout << "Количество вершин на самом нижнем уровне: " << bottomCount << endl;
    }
    else {
        cout << "Дерево пусто!" << endl;
    }

    cout << "\nКонец" << endl;
    system("pause");

    return 0;
}