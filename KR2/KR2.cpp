// ==================================================
// Лабораторная работа №2
// ==================================================
// Автор: Николаев Вячеслав Алексеевич
// Группа: 4335
// Вариант: 17
// Задача: E = (A ∩ B ∩ C) \ D (строчные русские буквы)
// Система: Visual Studio 2022 / C++17
// Дата: 31 мая 2026 г.
// ==================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Подключаем реализацию множества (меняется для разных способов)

#include "SetArrays.h"       // для массивов символов
// #include "SetLists.h"        // для линейных списков
// #include "SetBitArrays.h"    // для битовых массивов
// #include "SetMachineWord.h"  // для машинного слова

// измерение времени
void measureTime(int iterations, int setSize) {
    cout << "\n------------------------------------------------------------" << endl;
    cout << "измерение времени (мощность = " << setSize << ", итераций = " << iterations << ")" << endl;
    cout << "------------------------------------------------------------" << endl;

    Set A, B, C, D, E;

    A.generateRandom(setSize);
    B.generateRandom(setSize);
    C.generateRandom(setSize);
    D.generateRandom(setSize);

    cout << "тестовые множества:" << endl;
    A.print("a");
    B.print("b");
    C.print("c");
    D.print("d");
    cout << endl;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        E = (A & B & C) - D;
    }
    auto end = high_resolution_clock::now();
    double timeOp = duration_cast<duration<double>>(end - start).count();

    cout << "\nрезультат измерения времени (секунд на " << iterations << " операций):" << endl;
    cout << "  время: " << timeOp << " сек" << endl;
    cout << "  время на одну операцию: " << (timeOp / iterations) * 1000000 << " мкс" << endl;
    cout << "\nрезультат E = ";
    E.print();
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    srand(time(0));

    cout << "------------------------------------------------------------" << endl;
    cout << "Лабораторная работа №2" << endl;
    cout << "Вариант 17: e = (a & b & c) \\ d" << endl;
    cout << "Строчные русские буквы (а-я, ё)" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;

    // контрольный тест
    cout << "контрольный тест:" << endl;
    Set A("абвгде");
    Set B("бджз");
    Set C("дежзий");
    Set D("авик");
    Set E = (A & B & C) - D;

    A.print("a");
    B.print("b");
    C.print("c");
    D.print("d");
    cout << "ожидается: e = { д }" << endl;
    E.print("e");
    cout << endl;

    // проверка всех способов (если нужно сравнить)
    cout << "вычисление E = (A & B & C) - D" << endl;
    E = (A & B & C) - D;
    E.print("e");
    cout << endl;

    // измерение времени
    cout << "\nизмерение времени решения задачи" << endl;
    measureTime(100000, 10);
    measureTime(100000, 20);
    measureTime(100000, 33);

    return 0;
}