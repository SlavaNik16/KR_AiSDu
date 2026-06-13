// ==================================================
// Лабораторная работа №3
// ==================================================
// Автор: Николаев Вячеслав Алексеевич
// Группа: 4335
// Вариант: 17
// Задача: Двоичное дерево, ширинная разметка,
//         внутренний обход, количество вершин на самом нижнем уровне
// Система: Visual Studio 2022 / C++17
// Дата: Июнь 2026 г.
// ==================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Tree.h"

using namespace std;

// очистка буфера ввода
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    cout << "------------------------------------------------------------" << endl;
    cout << "Лабораторная работа №3" << endl;
    cout << "Вариант 17: Двоичное дерево" << endl;
    cout << "  - Ширинная разметка" << endl;
    cout << "  - Внутренний обход" << endl;
    cout << "  - Количество вершин на самом нижнем уровне" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;

    // выбор способа создания дерева
    int choice = 0;
    cout << "Выберите способ создания дерева:" << endl;
    cout << "  1. Случайная генерация" << endl;
    cout << "  2. Ручной ввод с клавиатуры" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    clearInput();
    cout << endl;

    Tree tree('a', 'z', 8);

    if (choice == 2) {
        cout << "Ручной ввод дерева." << endl;
        cout << "Правила ввода:" << endl;
        cout << "  - На каждый запрос введите 1 (создать узел) или 0 (не создавать)" << endl;
        cout << "  - Корень создаётся автоматически" << endl;
        cout << "  - Метки узлов будут присвоены автоматически (a, b, c, ...)" << endl;
        cout << endl;

        tree.makeTreeManual();
    }
    else {
        cout << "Случайная генерация дерева..." << endl;
        tree.makeTree();
    }

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

    cout << "\n=== Конец ===" << endl;
    system("pause");

    return 0;
}