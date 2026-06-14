#ifndef EDGE_H
#define EDGE_H

#include <iostream>
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

#endif