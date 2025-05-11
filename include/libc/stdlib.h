#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>

// Функции преобразования строк в числа
int atoi(const char* nptr);
long atol(const char* nptr);

// Функции выделения памяти
void* malloc(size_t size);
void* calloc(size_t nmemb, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

// Функции управления процессами
void exit(int status);
void abort(void);

#endif /* _STDLIB_H */