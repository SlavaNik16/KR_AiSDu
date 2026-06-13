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
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// класс "ребро графа"
class Edge {
private:
    int u;          // первая вершина
    int v;          // вторая вершина
    int weight;     // вес ребра

public:
    Edge() : u(0), v(0), weight(0) {}
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}

    int getU() const { return u; }
    int getV() const { return v; }
    int getWeight() const { return weight; }

    // для сортировки рёбер по весу
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

    void print() const {
        cout << "(" << char(u + 'A') << ", " << char(v + 'A') << ", " << weight << ")";
    }
};

// класс "система непересекающихся множеств" (DSU)
class DSU {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return false;
        }

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        }
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

// класс "граф"
class Graph {
private:
    int n;                      // количество вершин
    vector<Edge> edges;         // список всех рёбер
    vector<vector<pair<int, int> > > adjList;  // список смежности (для вывода)

    // отключённые конструкторы
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

public:
    // конструктор
    Graph(int vertices) : n(vertices) {
        adjList.resize(n);
    }

    // разрешаем перемещение
    Graph(Graph&& other) noexcept
        : n(other.n), edges(move(other.edges)), adjList(move(other.adjList)) {
        other.n = 0;
    }

    Graph& operator=(Graph&& other) noexcept {
        if (this != &other) {
            n = other.n;
            edges = move(other.edges);
            adjList = move(other.adjList);
            other.n = 0;
        }
        return *this;
    }

    // деструктор
    ~Graph() {
        edges.clear();
        adjList.clear();
    }

    // добавление ребра
    void addEdge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
        adjList[u].push_back(make_pair(v, weight));
        adjList[v].push_back(make_pair(u, weight));
    }

    // алгоритм Краскала
    pair<vector<Edge>, int> kruskalMST() {
        vector<Edge> mst;
        int totalWeight = 0;

        sort(edges.begin(), edges.end());

        DSU dsu(n);

        for (const Edge& edge : edges) {
            if (dsu.unite(edge.getU(), edge.getV())) {
                mst.push_back(edge);
                totalWeight += edge.getWeight();

                if (mst.size() == n - 1) {
                    break;
                }
            }
        }

        return make_pair(mst, totalWeight);
    }

    // вывод матрицы смежности
    void printAdjacencyMatrix() const {
        cout << "\nМатрица смежности:\n   ";
        for (int i = 0; i < n; i++) {
            cout << char('A' + i) << "  ";
        }
        cout << "\n  ";
        for (int i = 0; i < n; i++) {
            cout << "---";
        }
        cout << endl;

        vector<vector<int> > matrix(n, vector<int>(n, 0));
        for (size_t i = 0; i < edges.size(); i++) {
            const Edge& e = edges[i];
            matrix[e.getU()][e.getV()] = e.getWeight();
            matrix[e.getV()][e.getU()] = e.getWeight();
        }

        for (int i = 0; i < n; i++) {
            cout << char('A' + i) << " |";
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0 && i != j) {
                    cout << " - ";
                }
                else {
                    if (matrix[i][j] < 10) cout << " ";
                    cout << matrix[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    // вывод списка смежности
    void printAdjacencyList() const {
        cout << "\nСписок смежности:\n";
        for (int i = 0; i < n; i++) {
            cout << char('A' + i) << ": ";
            for (size_t k = 0; k < adjList[i].size(); k++) {
                int j = adjList[i][k].first;
                int w = adjList[i][k].second;
                cout << "(" << char('A' + j) << "," << w << ") ";
            }
            cout << endl;
        }
    }

    // вывод всех рёбер
    void printEdges() const {
        cout << "\nСписок всех рёбер:\n";
        for (size_t i = 0; i < edges.size(); i++) {
            cout << "  ";
            edges[i].print();
            cout << endl;
        }
    }

    // проверка связности графа
    bool isConnected() const {
        if (n == 0) return false;

        vector<bool> visited(n, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;
        int visitedCount = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (size_t k = 0; k < adjList[u].size(); k++) {
                int v = adjList[u][k].first;
                if (!visited[v]) {
                    visited[v] = true;
                    visitedCount++;
                    q.push(v);
                }
            }
        }

        return visitedCount == n;
    }

    int getVerticesCount() const { return n; }
    int getEdgesCount() const { return edges.size(); }
};

// класс для генерации случайного графа
class RandomGraphGenerator {
private:
    int n;          // количество вершин
    int m;          // количество рёбер
    int maxWeight;  // максимальный вес ребра

public:
    RandomGraphGenerator(int vertices, int edges, int maxW = 20)
        : n(vertices), m(edges), maxWeight(maxW) {
    }

    Graph generate() {
        Graph g(n);
        set<pair<int, int> > edgeSet;

        for (int i = 0; i < m; i++) {
            int u, v;
            do {
                u = rand() % n;
                v = rand() % n;
                if (u > v) swap(u, v);
            } while (u == v || edgeSet.find(make_pair(u, v)) != edgeSet.end());

            edgeSet.insert(make_pair(u, v));
            int weight = rand() % maxWeight + 1;
            g.addEdge(u, v, weight);
        }

        if (!g.isConnected()) {
            for (int i = 1; i < n; i++) {
                bool connected = false;
                for (int j = 0; j < i; j++) {
                    if (edgeSet.find(make_pair(j, i)) != edgeSet.end()) {
                        connected = true;
                        break;
                    }
                }
                if (!connected) {
                    int weight = rand() % maxWeight + 1;
                    g.addEdge(0, i, weight);
                    edgeSet.insert(make_pair(0, i));
                }
            }
        }

        return g;
    }
};

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

    if (choice == 1) {
        int n, m;
        cout << "Введите количество вершин: ";
        cin >> n;
        cout << "Введите количество рёбер: ";
        cin >> m;
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
        int n, m, maxWeight;
        cout << "Введите количество вершин: ";
        cin >> n;
        cout << "Введите количество рёбер: ";
        cin >> m;
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