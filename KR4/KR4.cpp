// ==================================================
// Лабораторная работа №4
// ==================================================
// Автор: Николаев Вячеслав Алексеевич
// Группа: 4335
// Вариант: 17
// Задача: Стягивающее дерево наименьшей стоимости
//         неориентированного графа с нагруженными рёбрами
//         (алгоритм Краскала)
// Система: Visual Studio 2022 / C++17
// Дата: Июнь 2026 г.
// ==================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Graph.h"
#include "RandomGraphGenerator.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    cout << "============================================================" << endl;
    cout << "Лабораторная работа №4" << endl;
    cout << "Вариант 17: Стягивающее дерево наименьшей стоимости" << endl;
    cout << "  - Алгоритм Краскала" << endl;
    cout << "  - Неориентированный граф с нагруженными рёбрами" << endl;
    cout << "============================================================" << endl;
    cout << endl;

    int choice = 0;
    cout << "Выберите способ ввода графа:" << endl;
    cout << "  1. Ручной ввод" << endl;
    cout << "  2. Случайная генерация" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    clearInput();
    cout << endl;

    Graph* graph = nullptr;
    int n, m, maxWeight;
    cout << "Введите количество вершин: ";
    cin >> n;
    cout << "Введите количество рёбер: ";
    cin >> m;

    if (choice == 1) {
        clearInput();

        if (n <= 0 || m < 0) {
            cout << "Ошибка: неверные данные!" << endl;
            return 1;
        }

        graph = new Graph(n);

        cout << "\nВведите рёбра в формате: начало конец вес" << endl;
        cout << "Вершины обозначаются буквами от A до " << char('A' + n - 1) << endl;

        for (int i = 0; i < m; i++) {
            char u, v;
            int w;
            cout << "Ребро " << i + 1 << ": ";
            cin >> u >> v >> w;
            clearInput();

            int uIdx = toupper(u) - 'A';
            int vIdx = toupper(v) - 'A';

            if (uIdx < 0 || uIdx >= n || vIdx < 0 || vIdx >= n) {
                cout << "  Ошибка: неверные вершины! Ребро пропущено." << endl;
                i--;
                continue;
            }

            graph->addEdge(uIdx, vIdx, w);
        }
    }
    else {
        cout << "Введите максимальный вес ребра: ";
        cin >> maxWeight;
        clearInput();

        if (n <= 0 || m < 0 || maxWeight <= 0) {
            cout << "Ошибка: неверные данные!" << endl;
            return 1;
        }

        RandomGraphGenerator generator(n, m, maxWeight);
        graph = new Graph(generator.generate());

        cout << "\nСгенерировано рёбер: " << graph->getEdgesCount() << endl;
    }

    if (graph && graph->getVerticesCount() > 0) {
        graph->printAdjacencyMatrix();
        graph->printAdjacencyList();
        graph->printEdges();

        cout << "\nПроверка связности графа: ";
        if (graph->isConnected()) {
            cout << "граф связный" << endl;
        }
        else {
            cout << "граф НЕ связный (MST не существует)" << endl;
        }

        cout << "\n============================================================" << endl;
        cout << "Алгоритм Краскала (поиск минимального остовного дерева)" << endl;
        cout << "============================================================" << endl;

        pair<vector<Edge>, int> result = graph->kruskalMST();
        vector<Edge> mst = result.first;
        int totalWeight = result.second;

        if (mst.size() == graph->getVerticesCount() - 1) {
            cout << "\nМинимальное остовное дерево (MST):" << endl;
            for (size_t i = 0; i < mst.size(); i++) {
                cout << "  ";
                mst[i].print();
                cout << endl;
            }
            cout << "\nОбщий вес MST: " << totalWeight << endl;
        }
        else {
            cout << "\nГраф несвязный, минимальное остовное дерево не существует!" << endl;
            cout << "Найдено компонент: " << mst.size() + 1 << endl;
        }
    }

    delete graph;

    cout << "\n=== Конец ===" << endl;
    system("pause");

    return 0;
}