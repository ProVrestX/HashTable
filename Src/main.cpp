#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "tools.h"
#include "file_hundler.h"
#include "list_hundler.h"
#include "table_hundler.h"

int main (int argc, char* argv[]) {

    size_t len = 0;
    char* data = NULL;

    HashTable* table = CreateTable(2048);

    switch(argc) {

        case 1:
            FillTableFromFile(table, "txt/test.txt");
            data = GetFileData("txt/test.txt", &len);
            break;
        
        case 2:
            FillTableFromFile(table, argv[1]);
            data = GetFileData(argv[1], &len);
            break;
        
        case 3:
            FillTableFromFile(table, argv[1]);
            data = GetFileData(argv[2], &len);
            break;
        
        default:
            FillTableFromFile(table, argv[1]);
            data = GetFileData(argv[2], &len);
            break;

    }

    char* word = (char*)calloc(32, 1);
    char* buf = (char*)calloc(1024, 1);
    int buf_len = 0;
    // char* trash = (char*)calloc(32, 1);

    FILE* file_res = fopen("txt/res.txt", "w");

    for(int i = 0; i < len;) {

        // int res = sscanf(data + i, "%[0-9a-zA-Z_`'-]", word);
        // int word_len = GetDataSize(word, 0);

        // int chk = CheckTableElement(table, word, word_len);
        // // printf("%d_ Check <%.*s>: %d\n", res, word_len, word, chk);
        // fprintf(file_res, "Check <%.*s>: %d\n", word_len, word, chk);

        // i += word_len;
        // sscanf(data + i, "%[^0-9a-zA-Z_`'-]", trash);
        // i += strlen(trash);

        int trash_size;
        memset(word, 0, 32);
        int word_len = StrCpy(word, data + i, &trash_size);
        if(!word_len) break;

        int chk = CheckTableElement(table, word, word_len);
        // printf("%d_ Check <%.*s>: %d\n", res, word_len, word, chk);
        // fprintf(file_res, "Check <%.*s>: %d\n", word_len, word, chk);

        buf_len += GetChkStr(buf + buf_len, word, word_len, chk);

        if(1024 - buf_len < 32) {
            fprintf(file_res, "%.*s", buf_len, buf);
            buf_len = 0;
        }


        i += word_len + trash_size;

    }
    fclose(file_res);
    free(word);
    free(buf);
    // free(trash);
    
    FILE* file_dump = fopen("txt/dump.txt", "w");
    DumpTable(table, file_dump);
    fclose(file_dump);


    DestroyTable(table);
    free(data);
    return 0;
}
