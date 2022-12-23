#ifndef __ALLOC__H__
#define __ALLOC__H__

void* realloc(void* ptr, size_t size);
void free(void* ptr);
void* malloc(size_t size);

char* itoa(int value, char* str, int base);
int atoi(const char* str);

void srand(unsigned int seed);
int rand(void);

int compare(const void* a, const void* b);
void* memcpy(void* dest, const void* src, size_t n);

#endif
