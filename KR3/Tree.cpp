#include "Tree.h"
#include <cstdlib>
#include <cstring>
using namespace std;

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

int Tree::getBottomLevelCount() {
    bottomLevelCount = 0;
    countBottomLevel(root, 0);
    return bottomLevelCount;
}

void Tree::printLevelOrder() {
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