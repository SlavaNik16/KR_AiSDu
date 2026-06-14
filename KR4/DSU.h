#ifndef DSU_H
#define DSU_H

#include <vector>
using namespace std;

// класс "система непересекающихся множеств" (DSU)
class DSU {
private:
    vector<int> parent; // родитель вершины
    vector<int> rank;   // ранг (глубина дерева)

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Алгоритм find (сжатие пути) - уменьшает высоту деревьев
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Алгоритм unite (объединение по рангу)
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

#endif