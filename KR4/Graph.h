#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include "Edge.h"
using namespace std;

// класс "граф"
class Graph {
private:
    int n;                              // количество вершин
    vector<Edge> edges;                 // список всех рёбер
    vector<vector<pair<int, int> > > adjList;  // список смежности

    // запрещаем копирование
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

public:
    Graph(int vertices);

    // разрешаем перемещение
    Graph(Graph&& other) noexcept;
    Graph& operator=(Graph&& other) noexcept;

    ~Graph();

    void addEdge(int u, int v, int weight);
    pair<vector<Edge>, int> kruskalMST();
    void printAdjacencyMatrix() const;
    void printAdjacencyList() const;
    void printEdges() const;
    bool isConnected() const;
    int getVerticesCount() const;
    int getEdgesCount() const;
};

#endif