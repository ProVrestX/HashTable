#ifndef LIST_H
#define LIST_H

#include "types.h"

// List* CreateList(void* data, int size);
List* CreateList(void* data);
void ListPush(List* main_list, List* new_list);
// int ListSearch(List* list, void* data, int size);
int ListSearch(List* list, __m256i data);
void DestroyList(List* list);


#endif