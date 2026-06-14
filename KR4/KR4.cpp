// ==================================================
// Курсовая работа №4
// ==================================================
// Автор: Николаев Вячеслав Алексеевич
// Группа: 4335
// Вариант: 17
// Задача: Стягивающее дерево наименьшей стоимости
//         неориентированного графа с нагруженными рёбрами
//         (алгоритм Краскала)
// Система: Visual Studio 2022 / C++17
// Дата: 7 июня 2026 г.
// ==================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Graph.h"
#include "RandomGraphGenerator.h"

#include <sstream>
#include <string>
#include <cctype>

#include <chrono>

using namespace std;
using namespace std::chrono;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
bool isNumber(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isVertex(char c) {
    c = toupper(c);
    return (c >= 'A' && c <= 'Z');
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(nullptr));

    cout << "============================================================" << endl;
    cout << "Курсовая работа №4" << endl;
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
        cout << "Пример: A B 5" << endl;
        cout << endl;

        int i = 0;
        while (i < m) {
            string line;
            cout << "Ребро " << i + 1 << ": ";
            getline(cin, line);

            stringstream ss(line);
            string uStr, vStr, wStr;
            ss >> uStr >> vStr >> wStr;

            if (uStr.empty() || vStr.empty() || wStr.empty()) {
                cout << "  Ошибка: нужно ввести 3 значения (начало конец вес). Попробуйте снова." << endl;
                continue;
            }

            string extra;
            if (ss >> extra) {
                cout << "  Ошибка: слишком много значений! Введите ровно 3 значения." << endl;
                continue;
            }

            if (uStr.length() != 1 || vStr.length() != 1) {
                cout << "  Ошибка: начало и конец должны быть одной буквой! Попробуйте снова." << endl;
                continue;
            }

            char uChar = toupper(uStr[0]);
            char vChar = toupper(vStr[0]);

            if (!isVertex(uChar) || !isVertex(vChar)) {
                cout << "  Ошибка: вершины должны быть буквами от A до Z! Попробуйте снова." << endl;
                continue;
            }

            if (!isNumber(wStr)) {
                cout << "  Ошибка: вес должен быть целым числом! Попробуйте снова." << endl;
                continue;
            }

            int uIdx = uChar - 'A';
            int vIdx = vChar - 'A';
            int weight = stoi(wStr);

            if (uIdx < 0 || uIdx >= n || vIdx < 0 || vIdx >= n) {
                cout << "  Ошибка: вершины должны быть от A до " << char('A' + n - 1) << "! Попробуйте снова." << endl;
                continue;
            }

            if (weight <= 0) {
                cout << "  Ошибка: вес должен быть положительным числом! Попробуйте снова." << endl;
                continue;
            }

            graph->addEdge(uIdx, vIdx, weight);
            i++;
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
        // выводим только если вершин не слишком много
        if (n <= 26) {
            graph->printAdjacencyMatrix();
            graph->printAdjacencyList();
            graph->printEdges();
        }
        else {
            cout << "\n(граф слишком большой, матрица и списки не выводятся на экран)" << endl;
            cout << "Количество вершин: " << n << endl;
            cout << "Количество рёбер: " << graph->getEdgesCount() << endl;
        }

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

        auto start = high_resolution_clock::now();
        pair<vector<Edge>, int> result = graph->kruskalMST(); 
        auto end = high_resolution_clock::now();
        double elapsed = duration<double>(end - start).count();

        cout << "\nВремя выполнения алгоритма Краскала: " << elapsed << " сек" << endl;
        cout << "Количество рёбер: " << graph->getEdgesCount() << endl;

        vector<Edge> mst = result.first;
        int totalWeight = result.second;

        if (mst.size() == graph->getVerticesCount() - 1) {
            cout << "\nМинимальное остовное дерево (MST):" << endl;
            for (auto i = 0; i < mst.size(); i++) {
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