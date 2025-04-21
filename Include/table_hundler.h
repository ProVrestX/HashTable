#ifndef TABLE_H
#define TABLE_H

#include "types.h"

HashTable* CreateTable(int size);
void AddTableElement(HashTable* table, List* element);
int CheckTableElement(HashTable* table, void* data, int size);
void DestroyTable(HashTable* table);
void FillTableFromStr(HashTable* table, char* str);
void FillTableFromFile(HashTable* table, char* name);
void DumpTable(HashTable* table, FILE* file_dump);

#endif