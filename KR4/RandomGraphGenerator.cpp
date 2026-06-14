#include "RandomGraphGenerator.h"
#include <set>
#include <cstdlib>
using namespace std;

RandomGraphGenerator::RandomGraphGenerator(int vertices, int edges, int maxW)
    : n(vertices), m(edges), maxWeight(maxW) {
}

Graph RandomGraphGenerator::generate() {
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