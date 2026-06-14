#ifndef RANDOM_GRAPH_GENERATOR_H
#define RANDOM_GRAPH_GENERATOR_H

#include "Graph.h"

// класс для генерации случайного графа
class RandomGraphGenerator {
private:
    int n;          // количество вершин
    int m;          // количество рёбер
    int maxWeight;  // максимальный вес ребра

public:
    RandomGraphGenerator(int vertices, int edges, int maxW = 20);
    Graph generate();
};

#endif