#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

// unsigned long long GetHash(void* data, int size) {

//     unsigned long long hash = 5381;

//     for(int i = 0; i < size; i++) {
//         hash = ((hash << 5) + hash) + (unsigned long long)(((char*)data)[i]);
//     }

//     return hash;
// }

// unsigned long long GetHash(__m256i data_vec) {

//     unsigned long long hash = 5381;
//     unsigned long long* data = (unsigned long long*)calloc(4, sizeof(unsigned long long));
//     _mm256_storeu_si256((__m256i*)data, data_vec);

//     for(int i = 0; i < 4; i++) {
//         hash = ((hash << 5) + hash) + data[i];
//     }

//     free(data);
//     return hash;
// }

int GetDataSize(void* data, char stop_symbol) {

    int size = 0;

    for(int i = 0; ((char*)data)[i] >= ' ' && ((char*)data)[i] != stop_symbol; i++) {
        size++;
    }

    return size;
}

int StrCpy(void* dest, void* src, int* trash_size) {
    int len_dest = 0;
    int len_trash = 0;
    char* src_chr = (char*)src;
    char* dest_chr = (char*)dest;
    
    while(!(('a' <= *src_chr && *src_chr <= 'z') || \
        ('A' <= *src_chr && *src_chr <= 'Z') || \
        ('0' <= *src_chr && *src_chr <= '9') || \
        (*src_chr == '_') || (*src_chr == '-'))) {
            src_chr++;
            len_trash++;
            if(*src_chr == 0) return 0;
        }
    if(trash_size) *trash_size = len_trash;

    while(('a' <= *src_chr && *src_chr <= 'z') || \
        ('A' <= *src_chr && *src_chr <= 'Z') || \
        ('0' <= *src_chr && *src_chr <= '9') || \
        (*src_chr == '_') || (*src_chr == '-')) {

            *dest_chr = *src_chr;
            src_chr++;
            dest_chr++; 
            len_dest++;
            if(len_dest == 31) break;
        }
    *dest_chr = 0;

    return len_dest;
}

int GetChkStr(char* buf, char* word, int word_len, int chk) {
    int ip = 0;

    memcpy(buf + ip, "Check <", 7);
    ip += 7;
    memcpy(buf + ip, word, word_len);
    ip += word_len;
    memcpy(buf + ip, ">: ", 3);
    ip += 3;
    buf[ip] = chk + '0';
    ip++;
    buf[ip] = '\n';
    ip++;

    return ip;
}

void Print_m256i(__m256i vec) {
    unsigned char str[33] = {0};
    
    printf("m256i as string: ");
    _mm256_storeu_si256((__m256i*)str, vec);
    str[32] = 0;
    
    printf("[%.32s]\n", str);
    
    printf("Hex values: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x ", str[i]);
    }
    printf("\n");

    return;
}