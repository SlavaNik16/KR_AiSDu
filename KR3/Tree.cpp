#include "Tree.h"
#include <cstdlib>
#include <cstring>
#include <stack>
using namespace std;

// вспомогательная функция для очистки буфера ввода
static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Tree::clearScreen() {
    for (int i = 0; i < maxDepth; i++) {
        for (int j = 0; j < 80; j++) {
            screen[i][j] = '.';
        }
    }
}

Node* Tree::makeNode(int depth, int& levelCount) {
    Node* v = nullptr;


    bool createNode = (depth < (rand() % 6 + 1)) && (currentTag <= maxTag);

    if (createNode) {
        v = new Node();
        v->tag = currentTag++;      
        levelCount++;             

        if (depth > maxLevel) {
            maxLevel = depth;
        }

        v->left = makeNode(depth + 1, levelCount);
        v->right = makeNode(depth + 1, levelCount);
    }
    return v;
}
Node* Tree::makeNodeManual(int depth, int& levelCount) {
    Node* v = nullptr;

    string indent = "";
    for (int i = 0; i < depth; i++) indent += "  ";

    int create = 0;

    if (depth >= maxDepth) {
        if (depth == 0) {
            cout << "Ошибка: maxDepth слишком мал для создания корня!" << endl;
            return nullptr;
        }
        cout << indent << "Достигнута максимальная глубина (" << maxDepth << "), узел НЕ создаётся" << endl;
        return nullptr;
    }

    if (depth == 0) {
        create = 1;
        cout << "Создание корня (глубина 0)" << endl;
    }
    else {
        cout << indent << "Создавать узел (глубина " << depth << ")? (1 - да, 0 - нет): ";
        cin >> create;
        clearInput();
    }

    if (create == 1 && currentTag <= maxTag) {
        v = new Node();
        v->tag = currentTag++;
        levelCount++;

        cout << indent << "  -> Узел " << v->tag << " создан" << endl;

        if (depth > maxLevel) {
            maxLevel = depth;
        }

        if (depth + 1 < maxDepth) {
            cout << indent << "  Левый сын для узла " << v->tag << ":" << endl;
            v->left = makeNodeManual(depth + 1, levelCount);

            cout << indent << "  Правый сын для узла " << v->tag << ":" << endl;
            v->right = makeNodeManual(depth + 1, levelCount);
        }
        else {
            cout << indent << "  Достигнута максимальная глубина, сыновья не создаются" << endl;
        }
    }
    else if (depth > 0 && create == 0) {
        cout << indent << "  -> Узел НЕ создан" << endl;
    }

    return v;
}


void Tree::placeNodes(Node* v, int row, int col) {
    if (!v) return;

    if (row >= 1 && row <= maxDepth && col >= 1 && col <= 79) {
        screen[row - 1][col - 1] = v->tag;
    }

    if (row < maxDepth) {
        int shift = (offset >> row); 
        if (v->left) placeNodes(v->left, row + 1, col - shift);
        if (v->right) placeNodes(v->right, row + 1, col + shift);
    }
}

void Tree::inorderTraversal(Node* v, vector<char>& result) {
    if (!v) return;
    inorderTraversal(v->left, result);
    result.push_back(v->tag);
    inorderTraversal(v->right, result);
}

void Tree::preorderTraversal(Node* v, vector<char>& result) {
    if (!v) return;
    result.push_back(v->tag);
    preorderTraversal(v->left, result);
    preorderTraversal(v->right, result);
}

void Tree::postorderTraversal(Node* v, vector<char>& result) {
    if (!v) return;
    postorderTraversal(v->left, result);
    postorderTraversal(v->right, result);
    result.push_back(v->tag);
}

void Tree::countBottomLevel(Node* v, int depth) {
    if (!v) return;

    if (depth == maxLevel) {
        bottomLevelCount++;
    }

    countBottomLevel(v->left, depth + 1);
    countBottomLevel(v->right, depth + 1);
}

Tree::Tree(char startTag, char endTag, int maxDepth)
    : root(nullptr),
    currentTag(startTag),
    maxTag(endTag),
    maxDepth(maxDepth),
    offset(40),
    bottomLevelCount(0),
    maxLevel(0) {

    screen = new char* [maxDepth];
    for (int i = 0; i < maxDepth; i++) {
        screen[i] = new char[80];
    }
}

Tree::~Tree() {
    if (root) delete root;
    for (int i = 0; i < maxDepth; i++) {
        delete[] screen[i];
    }
    delete[] screen;
}

void Tree::makeTree() {
    int levelCount = 0;
    root = makeNode(0, levelCount);
}

void Tree::makeTreeManual() {
    int levelCount = 0;
    cout << "Начинаем ручное построение дерева..." << endl;
    cout << "(метки будут присвоены автоматически: a, b, c, ...)" << endl;
    cout << "----------------------------------------" << endl;
    root = makeNodeManual(0, levelCount);
    cout << "----------------------------------------" << endl;
    cout << "Построение завершено. Всего создано узлов: " << levelCount << endl;
}


bool Tree::exists() const {
    return root != nullptr;
}

void Tree::outTree() {
    if (!root) {
        cout << "Дерево пусто!" << endl;
        return;
    }

    clearScreen();
    placeNodes(root, 1, offset);

    cout << "\nИзображение дерева:\n";
    for (int i = 0; i < maxDepth; i++) {
        screen[i][79] = '\0';
        cout << screen[i] << endl;
    }
    cout << endl;
}

vector<char> Tree::inorder() {
    vector<char> result;
    inorderTraversal(root, result);
    return result;
}

void Tree::printInorder() {
    vector<char> seq = inorder();
    cout << "Внутренний обход: ";
    for (char c : seq) {
        cout << c << " ";
    }
    cout << endl;
}

vector<char> Tree::preorder() {
    vector<char> result;
    preorderTraversal(root, result);
    return result;
}

void Tree::printPreorder() {
    vector<char> seq = preorder();
    cout << "Прямой обход: ";
    for (char c : seq) {
        cout << c << " ";
    }
    cout << endl;
}

vector<char> Tree::postorder() {
    vector<char> result;
    postorderTraversal(root, result);
    return result;
}

void Tree::printPostorder() {
    vector<char> seq = postorder();
    cout << "Обратный обход: ";
    for (char c : seq) {
        cout << c << " ";
    }
    cout << endl;
}

int Tree::getBottomLevelCount() {
    bottomLevelCount = 0;
    countBottomLevel(root, 0);
    return bottomLevelCount;
}

void Tree::printBFSLevels() {
    if (!root) {
        cout << "Дерево пусто!" << endl;
        return;
    }

    cout << "Ширинная разметка (по уровням):\n";
    queue<Node*> q;
    q.push(root);

    int level = 0;
    while (!q.empty()) {
        int levelSize = q.size();
        cout << "Уровень " << level << ": ";

        for (int i = 0; i < levelSize; i++) {
            Node* v = q.front();
            q.pop();
            cout << v->tag << " ";

            if (v->left) q.push(v->left);
            if (v->right) q.push(v->right);
        }
        cout << endl;
        level++;
    }
}

void Tree::printDFSLevels() {
    if (!root) {
        cout << "Дерево пусто!" << endl;
        return;
    }

    vector<vector<char>> levels;

    stack<pair<Node*, int>> st;
    st.push({ root, 0 });

    // Собираем все узлы в вектор по уровням
    while (!st.empty()) {
        Node* v = st.top().first;
        int level = st.top().second;
        st.pop();

        if (level >= levels.size()) {
            levels.resize(level + 1);
        }

        levels[level].push_back(v->tag);

        if (v->right) st.push({ v->right, level + 1 });
        if (v->left) st.push({ v->left, level + 1 });
    }

    cout << "Обход в глубину (по уровням):\n";
    for (int i = 0; i < levels.size(); i++) {
        cout << "Уровень " << i << ": ";
        for (char c : levels[i]) {
            cout << c << " ";
        }
        cout << endl;
    }
}

void Tree::printBFS() {
    if (!root) {
        cout << "Дерево пусто!" << endl;
        return;
    }

    cout << "Обход в ширину (BFS): ";
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* v = q.front();
        q.pop();
        cout << v->tag << " ";

        if (v->left) q.push(v->left);
        if (v->right) q.push(v->right);
    }
    cout << endl;
}

void Tree::printDFS() {
    if (!root) {
        cout << "Дерево пусто!" << endl;
        return;
    }

    cout << "Обход в глубину (DFS): ";
    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* v = st.top();
        st.pop();
        cout << v->tag << " ";

        if (v->right) st.push(v->right);
        if (v->left) st.push(v->left);
    }
    cout << endl;
}