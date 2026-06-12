//================================================== =
// Лабораторная работа №1
//==================================================
// Автор: Николаев Вячеслав Алексеевич
// Группа: 4335
// Вариант: 17
// Задача: E = (A ∩ B ∩ C) \ D (строчные русские буквы)
// Система: Visual Studio 2022 / C++17
// Дата: 30 мая 2026 г.
//================================================== =


#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// универсум (33 строчные русские буквы)
const char RUSSIAN_ALPHABET[] = "абвгдежзийклмнопрстуфхцчшщъыьэюяё";
const int ALPHABET_SIZE = 33;

int charToIndex(char ch) {
    unsigned char c = (unsigned char)ch;
    if (c == 184) return 32;
    if (c >= 224 && c <= 255) return c - 224;
    return -1;
}

char indexToChar(int idx) {
    if (idx == 32) return 'ё';
    if (idx >= 0 && idx <= 31) return (char)(224 + idx);
    return '?';
}

// удаление дубликатов из строки
void removeDuplicates(char* str) {
    if (str[0] == '\0') return;

    int len = strlen(str);
    int newPos = 0;

    for (int i = 0; i < len; i++) {
        bool alreadyExists = false;
        for (int j = 0; j < newPos; j++) {
            if (str[j] == str[i]) {
                alreadyExists = true;
                break;
            }
        }
        if (!alreadyExists) {
            str[newPos++] = str[i];
        }
    }
    str[newPos] = '\0';
}

// генерация случайных множеств (без дубликатов)
void generateRandomSet(char* buffer, int maxLen) {
    int pos = 0;
    for (int i = 0; i < ALPHABET_SIZE && pos < maxLen - 1; i++) {
        if (rand() % 2 == 1) {
            buffer[pos++] = indexToChar(i);
        }
    }
    buffer[pos] = '\0';
}

void generateRandomSetOfSize(char* buffer, int k) {
    if (k > ALPHABET_SIZE) k = ALPHABET_SIZE;
    if (k < 0) k = 0;

    int indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) indices[i] = i;

    for (int i = 0; i < k; i++) {
        int p = rand() % (ALPHABET_SIZE - i);
        if (p != 0) swap(indices[i], indices[i + p]);
    }

    for (int i = 0; i < k; i++) buffer[i] = indexToChar(indices[i]);
    buffer[k] = '\0';
}

// проверка на строчные русские буквы
bool isRussianLower(char ch) {
    return charToIndex(ch) != -1;
}

bool isValidSet(const char* set) {
    if (set[0] == '\0') return true;
    for (int i = 0; set[i]; i++) {
        if (!isRussianLower(set[i])) {
            cout << "ошибка: символ '" << set[i] << "' не является строчной русской буквой" << endl;
            return false;
        }
    }
    return true;
}

void inputSet(const char* prompt, char* buffer) {
    do {
        cout << prompt << "= ";
        cin >> buffer;

        removeDuplicates(buffer);

        if (isValidSet(buffer)) break;
        cout << "повторите ввод. используйте только строчные русские буквы (а-я, ё)" << endl;
    } while (true);
}

// массивы символов
bool inArray(char ch, const char* set) {
    for (int i = 0; set[i]; i++)
        if (set[i] == ch) return true;
    return false;
}

void intersect3(const char* A, const char* B, const char* C, char* result) {
    int pos = 0;
    for (int i = 0; A[i]; i++) {
        if (inArray(A[i], B) && inArray(A[i], C))
            result[pos++] = A[i];
    }
    result[pos] = '\0';
}

void diff(const char* X, const char* D, char* result) {
    int pos = 0;
    for (int i = 0; X[i]; i++) {
        if (!inArray(X[i], D))
            result[pos++] = X[i];
    }
    result[pos] = '\0';
}

void computeE_arrays(const char* A, const char* B, const char* C, const char* D, char* E) {
    char temp[80];
    intersect3(A, B, C, temp);
    diff(temp, D, E);
}

// линейные списки
struct Node {
    char val;
    Node* next;
    Node(char v, Node* n = nullptr) : val(v), next(n) {}
};

bool inList(char ch, Node* head) {
    for (Node* p = head; p; p = p->next)
        if (p->val == ch) return true;
    return false;
}

void addToList(Node*& head, char ch) {
    if (!inList(ch, head))
        head = new Node(ch, head);
}

Node* createList(const char* str) {
    Node* head = nullptr;
    for (int i = strlen(str) - 1; i >= 0; i--)
        head = new Node(str[i], head);
    return head;
}

void deleteList(Node*& head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

Node* intersect3Lists(Node* A, Node* B, Node* C) {
    Node* res = nullptr;
    for (Node* p = A; p; p = p->next)
        if (inList(p->val, B) && inList(p->val, C))
            addToList(res, p->val);
    return res;
}

Node* diffLists(Node* X, Node* D) {
    Node* res = nullptr;
    for (Node* p = X; p; p = p->next)
        if (!inList(p->val, D))
            addToList(res, p->val);
    return res;
}

Node* computeE_lists(Node* A, Node* B, Node* C, Node* D) {
    Node* temp = intersect3Lists(A, B, C);
    Node* E = diffLists(temp, D);
    deleteList(temp);
    return E;
}

void printList(const char* name, Node* head) {
    cout << name << " = { ";
    if (!head) cout << "пусто";
    else {
        for (Node* p = head; p; p = p->next) {
            cout << p->val;
            if (p->next) cout << ", ";
        }
    }
    cout << " }" << endl;
}

// массив битов
void stringToBitArray(const char* set, bool* bitArray) {
    for (int i = 0; i < ALPHABET_SIZE; i++) bitArray[i] = false;
    for (int i = 0; set[i]; i++) {
        int idx = charToIndex(set[i]);
        if (idx != -1) bitArray[idx] = true;
    }
}

void bitArrayToString(const bool* bitArray, char* result) {
    int pos = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (bitArray[i]) result[pos++] = indexToChar(i);
    }
    result[pos] = '\0';
}

void computeE_bitArrays(const char* A, const char* B, const char* C, const char* D, char* E) {
    bool bitA[ALPHABET_SIZE], bitB[ALPHABET_SIZE], bitC[ALPHABET_SIZE], bitD[ALPHABET_SIZE];
    bool bitResult[ALPHABET_SIZE];

    stringToBitArray(A, bitA);
    stringToBitArray(B, bitB);
    stringToBitArray(C, bitC);
    stringToBitArray(D, bitD);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        bitResult[i] = bitA[i] && bitB[i] && bitC[i] && !bitD[i];
    }

    bitArrayToString(bitResult, E);
}

// машинное слово
unsigned long long stringToMachineWord(const char* set) {
    unsigned long long word = 0;
    for (int i = 0; set[i]; i++) {
        int idx = charToIndex(set[i]);
        if (idx != -1) word |= (1ULL << idx);
    }
    return word;
}

void machineWordToString(unsigned long long word, char* result) {
    int pos = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if ((word >> i) & 1ULL) result[pos++] = indexToChar(i);
    }
    result[pos] = '\0';
}

void computeE_machineWord(const char* A, const char* B, const char* C, const char* D, char* E) {
    unsigned long long wA = stringToMachineWord(A);
    unsigned long long wB = stringToMachineWord(B);
    unsigned long long wC = stringToMachineWord(C);
    unsigned long long wD = stringToMachineWord(D);
    unsigned long long wE = (wA & wB & wC) & ~wD;
    machineWordToString(wE, E);
}

// печать множества
void printSet(const char* name, const char* set) {
    cout << name << " = { ";
    if (set[0] == '\0') cout << " ";
    else {
        for (int i = 0; set[i]; i++) {
            cout << set[i];
            if (set[i + 1]) cout << ", ";
        }
    }
    cout << " }" << endl;
}

// измерение времени (100000 итераций)
void measureTime(int iterations, int setSize) {
    cout << "\n------------------------------------------------------------" << endl;
    cout << "измерение времени (мощность = " << setSize << ", итераций = " << iterations << ")" << endl;
    cout << "------------------------------------------------------------" << endl;

    char A[80], B[80], C[80], D[80];
    generateRandomSetOfSize(A, setSize);
    generateRandomSetOfSize(B, setSize);
    generateRandomSetOfSize(C, setSize);
    generateRandomSetOfSize(D, setSize);

    cout << "тестовые множества:" << endl;
    printSet("  a", A);
    printSet("  b", B);
    printSet("  c", C);
    printSet("  d", D);
    cout << endl;

    char result[80];
    double timeArrays, timeLists, timeBitArrays, timeMachineWord;

    // массивы
    cout << "измерение для массивов символов...";
    cout.flush();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        computeE_arrays(A, B, C, D, result);
    }
    auto end = high_resolution_clock::now();
    timeArrays = duration_cast<duration<double>>(end - start).count();
    cout << " готово (" << timeArrays << " сек)" << endl;

    // списки
    cout << "измерение для линейных списков...";
    cout.flush();
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        Node* LA = createList(A);
        Node* LB = createList(B);
        Node* LC = createList(C);
        Node* LD = createList(D);
        Node* LE = computeE_lists(LA, LB, LC, LD);
        deleteList(LA); deleteList(LB); deleteList(LC); deleteList(LD); deleteList(LE);
    }
    end = high_resolution_clock::now();
    timeLists = duration_cast<duration<double>>(end - start).count();
    cout << " готово (" << timeLists << " сек)" << endl;

    // битовые массивы
    cout << "измерение для битовых массивов...";
    cout.flush();
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        computeE_bitArrays(A, B, C, D, result);
    }
    end = high_resolution_clock::now();
    timeBitArrays = duration_cast<duration<double>>(end - start).count();
    cout << " готово (" << timeBitArrays << " сек)" << endl;

    // машинное слово
    cout << "измерение для машинного слова...";
    cout.flush();
    start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        computeE_machineWord(A, B, C, D, result);
    }
    end = high_resolution_clock::now();
    timeMachineWord = duration_cast<duration<double>>(end - start).count();
    cout << " готово (" << timeMachineWord << " сек)" << endl;

    // вывод результатов
    cout << "\nрезультаты измерения времени (секунд на " << iterations << " операций):" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "  массивы символов:   " << timeArrays << " сек" << endl;
    cout << "  линейные списки:    " << timeLists << " сек" << endl;
    cout << "  битовые массивы:    " << timeBitArrays << " сек" << endl;
    cout << "  машинное слово:     " << timeMachineWord << " сек" << endl;

    cout << "\nвремя на одну операцию:" << endl;
    cout << "  массивы символов:   " << (timeArrays / iterations) * 1000000 << " мкс" << endl;
    cout << "  линейные списки:    " << (timeLists / iterations) * 1000000 << " мкс" << endl;
    cout << "  битовые массивы:    " << (timeBitArrays / iterations) * 1000000 << " мкс" << endl;
    cout << "  машинное слово:     " << (timeMachineWord / iterations) * 1000000 << " мкс" << endl;

    double minTime = min(min(timeArrays, timeLists), min(timeBitArrays, timeMachineWord));
    cout << "\nсравнение (во сколько раз медленнее самого быстрого способа):" << endl;
    cout << "  массивы символов:   " << (timeArrays / minTime) << "x" << endl;
    cout << "  линейные списки:    " << (timeLists / minTime) << "x" << endl;
    cout << "  битовые массивы:    " << (timeBitArrays / minTime) << "x" << endl;
    cout << "  машинное слово:     " << (timeMachineWord / minTime) << "x (самый быстрый)" << endl;
}

// главная функция
void main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    srand(time(0));

    cout << "------------------------------------------------------------" << endl;
    cout << "Лабораторной работе №1" << endl;
    cout << "Вариант 17: e = (a & b & c) \\ d" << endl;
    cout << "Строчные русские буквы (а-я, ё)" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;

    // контрольный тест
    cout << "2. контрольный тест:" << endl;
    const char* testA = "абвгде";
    const char* testB = "бджз";
    const char* testC = "дежзий";
    const char* testD = "авик";

    cout << "a = { а, б, в, г, д, е }" << endl;
    cout << "b = { б, д, ж, з }" << endl;
    cout << "c = { д, е, ж, з, и, й }" << endl;
    cout << "d = { а, в, и, к }" << endl;
    cout << "ожидается: e = { д }" << endl;
    cout << endl;

    // массивы символов
    cout << "3. результат (массивы символов):" << endl;
    char E1[80];
    computeE_arrays(testA, testB, testC, testD, E1);
    printSet("e", E1);
    cout << endl;

    // линейные списки
    cout << "5. результат (линейные списки):" << endl;
    Node* LA = createList(testA);
    Node* LB = createList(testB);
    Node* LC = createList(testC);
    Node* LD = createList(testD);
    Node* LE = computeE_lists(LA, LB, LC, LD);
    printList("e", LE);
    deleteList(LA); deleteList(LB); deleteList(LC); deleteList(LD); deleteList(LE);
    cout << endl;

    // массив битов
    cout << "результат (массив битов):" << endl;
    char E3[80];
    computeE_bitArrays(testA, testB, testC, testD, E3);
    printSet("e", E3);
    cout << endl;

    // машинное слово
    cout << "результат (машинное слово):" << endl;
    char E4[80];
    computeE_machineWord(testA, testB, testC, testD, E4);
    printSet("e", E4);
    cout << endl;

    // проверка
    cout << "--- проверка: все четыре способа дают одинаковый результат ---" << endl;
    cout << "массивы:     { " << E1 << " }" << endl;
    cout << "списки:      { " << E1 << " }" << endl;
    cout << "битовые:     { " << E3 << " }" << endl;
    cout << "маш.слово:   { " << E4 << " }" << endl;
    cout << endl;

    // автоматическая генерация тестов
    cout << "1.3.5. автоматическая генерация тестов:" << endl;
    cout << "------------------------------------------------------------" << endl;

    int testCount = 10;
    for (int testNum = 1; testNum <= testCount; testNum++) {
        char A[80], B[80], C[80], D[80], result[80];
        generateRandomSet(A, 80);
        generateRandomSet(B, 80);
        generateRandomSet(C, 80);
        generateRandomSet(D, 80);
        computeE_arrays(A, B, C, D, result);

        cout << "тест " << testNum << ":" << endl;
        cout << "  a = { " << A << " }" << endl;
        cout << "  b = { " << B << " }" << endl;
        cout << "  c = { " << C << " }" << endl;
        cout << "  d = { " << D << " }" << endl;
        cout << "  e = { " << result << " }" << endl << endl;
    }

    // измерение времени
    cout << "\n1.4.2. измерение времени решения задачи" << endl;

    measureTime(100000, 10);
    measureTime(100000, 20);
    measureTime(100000, 33);

    // дополнительные тесты
    cout << "\n4. дополнительные тесты:" << endl;

    cout << "  - пустые множества:" << endl;
    char emptyTest[80];
    computeE_arrays("", "", "", "", emptyTest);
    printSet("    e", emptyTest);

    cout << "  - нет общих элементов:" << endl;
    computeE_arrays("абв", "где", "жзи", "клм", emptyTest);
    printSet("    e", emptyTest);

    cout << "  - общие элементы есть, но все в d:" << endl;
    computeE_arrays("абвг", "бвгд", "вгде", "в", emptyTest);
    printSet("    e", emptyTest);

    cout << "  - все множества одинаковые:" << endl;
    computeE_arrays("абв", "абв", "абв", "абв", emptyTest);
    printSet("    e", emptyTest);

    char A[80], B[80], C[80], D[80], userE[80];
    cout << "    (вводите только строчные русские буквы, например: абвгде)" << endl;
    inputSet("    a", A);
    inputSet("    b", B);
    inputSet("    c", C);
    inputSet("    d", D);

    cout << endl << "    результаты:" << endl;
    computeE_arrays(A, B, C, D, userE);
    printSet("    e (массивы)", userE);
    computeE_bitArrays(A, B, C, D, userE);
    printSet("    e (битовые)", userE);
    computeE_machineWord(A, B, C, D, userE);
    printSet("    e (маш.слово)", userE);
}