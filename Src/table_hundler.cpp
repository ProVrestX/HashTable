#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "tools.h"
#include "table_hundler.h"
#include "file_hundler.h"
#include "list_hundler.h"

HashTable* CreateTable(int size) {

    HashTable* table = (HashTable*)calloc(1, sizeof(HashTable));
    if(!table) return NULL;

    table->size = size;
    table->table = (List**)calloc(size, sizeof(List*));

    return table;
}

// void AddTableElement(HashTable* table, List* element) {

//     if(!table || !element) {
//         fprintf(stderr, "AddTableElement Error\n");
//         return;
//     }

//     int pos = element->hash % table->size;

//     if(table->table[pos]) {

//         if(ListSearch(table->table[pos], element->data, element->size) == 0)
//             ListPush(table->table[pos], element);
//         else
//             DestroyList(element);

//     }
//     else {
//         table->table[pos] = element;
//     }

//     return;
// }

void AddTableElement(HashTable* table, List* element) {

    if(!table || !element) {
        fprintf(stderr, "AddTableElement Error\n");
        return;
    }
    // Print_m256i(element->data);
    int pos = element->hash % table->size;

    if(table->table[pos]) {

        if(ListSearch(table->table[pos], element->data) == 0)
            ListPush(table->table[pos], element);
        else
            DestroyList(element);

    }
    else {
        table->table[pos] = element;
    }

    return;
}

// int CheckTableElement(HashTable* table, void* data, int size) {

//     if(!table || !data) {
//         fprintf(stderr, "CheckTableElement Error\n");
//         return -1;
//     }

//     int pos = GetHash(data, size) % table->size;

//     return table->table[pos] && ListSearch(table->table[pos], data, size);
// }

int CheckTableElement(HashTable* table, void* data, int size) {

    if(!table || !data) {
        fprintf(stderr, "CheckTableElement Error\n");
        return -1;
    }
    __m256i data_vec = _mm256_loadu_si256((__m256i*)data);

    int pos = GetHash(data_vec) % table->size;

    return table->table[pos] && ListSearch(table->table[pos], data_vec);
}

void DestroyTable(HashTable* table) {

    if(!table) return;

    for(int i = 0; i < table->size; i++) {
        DestroyList(table->table[i]);
    }

    free(table->table);
    free(table);

    return;
}

// void FillTableFromStr(HashTable* table, char* str) {

//     int len = strlen(str);
//     char* word = (char*)malloc(32);


//     for(int i = 0; i < len;) {

//         int trash_size;
//         int word_len = StrCpy(word, str + i, &trash_size);
//         if(!word_len) break;

//         // printf("data (%d): %.*s, hash = %LX\n", word_len, word_len, str + i, GetHash(_mm256_loadu_si256((__m256i*)(str + i))));
//         AddTableElement(table, CreateList(word, word_len));

//         i += word_len + trash_size;

//     }

//     free(word);
//     return;
// }

void FillTableFromStr(HashTable* table, char* str) {

    int len = strlen(str);
    char* word = (char*)malloc(32);

    for(int i = 0; i < len;) {

        int trash_size;
        memset(word, 0, 32);
        int word_len = StrCpy(word, str + i, &trash_size);
        if(!word_len) break;

        // printf("data (%d): %.*s, hash = %LX\n", word_len, word_len, str + i, GetHash(_mm256_loadu_si256((__m256i*)(str + i))));
        AddTableElement(table, CreateList(word));

        i += word_len + trash_size;

    }

    free(word);

    return;
}

void FillTableFromFile(HashTable* table, char* name) {

    char* str = GetFileData(name, NULL);
    FillTableFromStr(table, str);

    free(str);
    return;
}

// void DumpTable(HashTable* table, FILE* file_dump) {

//     if(!file_dump) file_dump = stdout;

//     fprintf(file_dump, "\nDump Table:\n");

//     for(int i = 0; i < table->size; i++) {

//         fprintf(file_dump, " %d: %p\n  ", i, table->table[i]);

//         if(table->table[i]) {
//             List* lst = table->table[i];

//             while(lst) {
//                 fprintf(file_dump, "%.*s; ", lst->size, (char*)lst->data);
//                 lst = lst->next;
//             }

//             fprintf(file_dump, "\n");
//         }

//         else {
//             fprintf(file_dump, "None\n");
//         }

//     }

//     return;
// }

void DumpTable(HashTable* table, FILE* file_dump) {

    if(!file_dump) file_dump = stdout;
    char* word = (char*)malloc(32);

    fprintf(file_dump, "\nDump Table:\n");

    for(int i = 0; i < table->size; i++) {

        fprintf(file_dump, " %d: %p\n  ", i, table->table[i]);

        if(table->table[i]) {
            List* lst = table->table[i];

            while(lst) {
                _mm256_storeu_si256((__m256i*)word, lst->data);
                fprintf(file_dump, "%s; ", word);

                lst = lst->next;
            }

            fprintf(file_dump, "\n");
        }

        else {
            fprintf(file_dump, "None\n");
        }

    }

    free(word);
    return;
}
