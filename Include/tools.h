#ifndef TOOLS_H
#define TOOLS_H

// unsigned long long GetHash(void* data, int size);
// unsigned long long GetHash(__m256i data);
extern "C" unsigned long long GetHash(__m256i data);
int GetDataSize(void* data, char stop_symbol);
int StrCpy(void* dest, void* src, int* trash_size);
int GetChkStr(char* buf, char* word, int word_len, int chk);
void Print_m256i(__m256i vec);

#endif