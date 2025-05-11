#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

// Копирование участка памяти
void* memcpy(void* dest, const void* src, size_t n);

// Установка участка памяти заданным байтом
void* memset(void* s, int c, size_t n);

// Сравнение участков памяти
int memcmp(const void* s1, const void* s2, size_t n);

// Копирование строки
char* strcpy(char* dest, const char* src);

// Копирование строки с ограничением длины
char* strncpy(char* dest, const char* src, size_t n);

// Конкатенация строк
char* strcat(char* dest, const char* src);

// Конкатенация строк с ограничением длины
char* strncat(char* dest, const char* src, size_t n);

// Сравнение строк
int strcmp(const char* s1, const char* s2);

// Сравнение строк с ограничением длины
int strncmp(const char* s1, const char* s2, size_t n);

// Определение длины строки
size_t strlen(const char* s);

// Поиск символа в строке
char* strchr(const char* s, int c);

// Поиск символа в строке с конца
char* strrchr(const char* s, int c);

// Поиск любого из указанных символов в строке
char* strpbrk(const char* s, const char* accept);

// Поиск подстроки в строке
char* strstr(const char* haystack, const char* needle);

#endif /* _STRING_H */