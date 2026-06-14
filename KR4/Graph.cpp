#include "Graph.h"
#include "DSU.h"
#include <algorithm>
using namespace std;

Graph::Graph(int vertices) : n(vertices) {
    adjList.resize(n);
}

Graph::Graph(Graph&& other) noexcept
    : n(other.n), edges(move(other.edges)), adjList(move(other.adjList)) {
    other.n = 0;
}

Graph& Graph::operator=(Graph&& other) noexcept {
    if (this != &other) {
        n = other.n;
        edges = move(other.edges);
        adjList = move(other.adjList);
        other.n = 0;
    }
    return *this;
}

Graph::~Graph() {
    edges.clear();
    adjList.clear();
}

void Graph::addEdge(int u, int v, int weight) {
    edges.push_back(Edge(u, v, weight));
    adjList[u].push_back(make_pair(v, weight));
    adjList[v].push_back(make_pair(u, weight));
}

pair<vector<Edge>, int> Graph::kruskalMST() {
    vector<Edge> mst;
    int totalWeight = 0;

    sort(edges.begin(), edges.end());
    DSU dsu(n);

    for (const Edge& edge : edges) {
        if (dsu.unite(edge.getU(), edge.getV())) {
            mst.push_back(edge);
            totalWeight += edge.getWeight();
            if (mst.size() == n - 1) break;
        }
    }

    return make_pair(mst, totalWeight);
}

void Graph::printAdjacencyMatrix() const {
    vector<vector<int> > matrix(n, vector<int>(n, 0));

    for (auto i = 0; i < edges.size(); i++) {
        const Edge& e = edges[i];
        matrix[e.getU()][e.getV()] = e.getWeight();
        matrix[e.getV()][e.getU()] = e.getWeight();
    }

    cout << "\nМатрица смежности:\n   ";
    for (int i = 0; i < n; i++) {
        cout << char('A' + i) << "  ";
    }
    cout << "\n  ";
    for (int i = 0; i < n; i++) cout << "---";
    cout << endl;

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

void Graph::printAdjacencyList() const {
    cout << "\nСписок смежности:\n";
    for (int i = 0; i < n; i++) {
        cout << char('A' + i) << ": ";
        for (auto k = 0; k < adjList[i].size(); k++) {
            int j = adjList[i][k].first;
            int w = adjList[i][k].second;
            cout << "(" << char('A' + j) << "," << w << ") ";
        }
        cout << endl;
    }
}

void Graph::printEdges() const {
    cout << "\nСписок всех рёбер:\n";
    for (auto i = 0; i < edges.size(); i++) {
        cout << "  ";
        edges[i].print();
        cout << endl;
    }
}

bool Graph::isConnected() const {
    if (n == 0) return false;

    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;
    int visitedCount = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto k = 0; k < adjList[u].size(); k++) {
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

int Graph::getVerticesCount() const { return n; }
int Graph::getEdgesCount() const { return edges.size(); }