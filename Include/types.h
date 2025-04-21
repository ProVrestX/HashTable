#ifndef TYPES_H
#define TYPES_H

#include <immintrin.h>

// typedef struct List {
//     void* data;
//     int size;
//     unsigned long long hash;
//     List* next;
// } List;

typedef struct List {
    __m256i data;
    unsigned long long hash;
    List* next;
} List;

typedef struct HashTable {
    int size;
    List** table;
} HashTable;

#endif