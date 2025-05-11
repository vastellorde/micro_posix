#include <libc/stdio.h>
#include <arch/i386/tty.h>

// Вывод символа
int putchar(int c) {
    terminal_putchar((char)c);
    return c;
}

// Вывод строки с переводом строки
int puts(const char* str) {
    terminal_writestring(str);
    terminal_putchar('\n');
    return 0;
}

// Форматированный вывод с использованием списка аргументов
int vprintf(const char* format, va_list args) {
    int written = 0;

    while (*format != '\0') {
        if (*format != '%') {
            putchar(*format);
            written++;
        } else {
            format++;

            switch (*format) {
                case 'c': {
                    char c = (char)va_arg(args, int);
                    putchar(c);
                    written++;
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);
                    if (str == NULL) {
                        str = "(null)";
                    }
                    while (*str) {
                        putchar(*str++);
                        written++;
                    }
                    break;
                }
                case 'd':
                case 'i': {
                    int value = va_arg(args, int);
                    if (value < 0) {
                        putchar('-');
                        written++;
                        value = -value;
                    }

                    char buffer[20];
                    int i = 0;
                    do {
                        buffer[i++] = '0' + (value % 10);
                        value /= 10;
                    } while (value > 0);

                    while (--i >= 0) {
                        putchar(buffer[i]);
                        written++;
                    }
                    break;
                }
                case 'x': {
                    unsigned int value = va_arg(args, unsigned int);
                    char buffer[20];
                    int i = 0;
                    do {
                        int digit = value % 16;
                        buffer[i++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
                        value /= 16;
                    } while (value > 0);

                    while (--i >= 0) {
                        putchar(buffer[i]);
                        written++;
                    }
                    break;
                }
                case '%': {
                    putchar('%');
                    written++;
                    break;
                }
                default:
                    putchar('%');
                    putchar(*format);
                    written += 2;
                    break;
            }
        }

        format++;
    }

    return written;
}

// Простая реализация printf
int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = vprintf(format, args);
    va_end(args);
    return result;
}