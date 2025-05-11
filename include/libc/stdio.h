#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>

// Функции ввода-вывода
int printf(const char* format, ...);
int vprintf(const char* format, va_list ap);
int putchar(int c);
int puts(const char* s);

#endif /* _STDIO_H */