#ifndef UTILS_H
#define UTILS_H

// универсум (33 строчные русские буквы)
const char RUSSIAN_ALPHABET[] = "абвгдежзийклмнопрстуфхцчшщъыьэюяё";
const int ALPHABET_SIZE = 33;

// преобразование буквы в индекс (0..32)
inline int charToIndex(char ch) {
    unsigned char c = (unsigned char)ch;
    if (c == 184) return 32;    
    if (c >= 224 && c <= 255) return c - 224; 
    return -1;  // не русская буква
}

// преобразование индекса в букву
inline char indexToChar(int idx) {
    if (idx == 32) return 'ё';
    if (idx >= 0 && idx <= 31) return (char)(224 + idx);
    return '?';
}
#endif