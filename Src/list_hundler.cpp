#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "tools.h"

// List* CreateList(void* data, int size) {

//     List* list = (List*)calloc(1, sizeof(List));
//     if(!list) return NULL;

//     list->size = size;
//     list->next = NULL;
    
//     list->data = malloc(size);
//     if(!list->data) return NULL;
//     memcpy(list->data, data, size);
//     list->hash = GetHash(list->data, size);

//     return list;
// }

List* CreateList(void* data) {
    if (!data) return NULL;

    List* list = (List*)aligned_alloc(32, sizeof(List));
    if (!list) return NULL;

    list->data = _mm256_loadu_si256((__m256i*)data);


    list->hash = GetHash(list->data);
    list->next = NULL;

    return list;
}

void ListPush(List* main_list, List* new_list) {

    if(!main_list || !new_list) return;

    while(main_list->next != NULL) 
        main_list = main_list->next;

    main_list->next = new_list;
    return;
}

// int ListSearch(List* list, void* data, int size) {

//     if(!list || !data) return -1;


//     while(list->next != NULL) {

//         if(list->size == size && !memcmp(list->data, data, size)) {
//             return 1;
//         }

//         list = list->next;
//     }

//     return list->size == size && !memcmp(list->data, data, size);
// }

int ListSearch(List* list, __m256i data) {

    if(!list) return -1;


    while(list->next != NULL) {

        if(_mm256_testc_si256(list->data, data)) {
            return 1;
        }

        list = list->next;
    }

    return _mm256_testc_si256(list->data, data);
}

// void DestroyList(List* list) {

//     if(!list) return;

//     free(list->data);
//     DestroyList(list->next);

//     free(list);
//     return;
// }

void DestroyList(List* list) {

    if(!list) return;

    // free(list->data);
    DestroyList(list->next);

    free(list);
    return;
}