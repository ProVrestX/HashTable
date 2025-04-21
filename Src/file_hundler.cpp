#include <stdio.h>
#include <stdlib.h>

#include "file_hundler.h"


char* GetFileData(const char* name, size_t* len) {

    FILE* file = fopen(name, "r");

    if(!file) {
        fprintf(stderr, "GetFileData Error (file: %s)\n", name);
        return NULL;
    }

    int file_len = GetFileLen(file);
    char* data = (char*)calloc(file_len + 1, 1);
    data[file_len] = 0;

    fread(data, file_len, 1, file);
    if(len) *len = file_len;

    fclose(file);
    return data;
}

int GetFileLen(FILE* file) {

    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    fseek(file, 0, SEEK_SET);

    return len;
}