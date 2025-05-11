#ifndef ARCH_I386_GDT_H
#define ARCH_I386_GDT_H

#include <stdint.h>

// Структура для записи GDT
struct gdt_entry {
    uint16_t limit_low;     // Младшие биты лимита (0-15)
    uint16_t base_low;      // Младшие биты базы (0-15)
    uint8_t  base_middle;   // Следующие биты базы (16-23)
    uint8_t  access;        // Биты доступа
    uint8_t  granularity;   // Гранулярность и старшие биты лимита
    uint8_t  base_high;     // Старшие биты базы (24-31)
} __attribute__((packed));

// Структура для указателя GDT
struct gdt_ptr {
    uint16_t limit;         // Размер GDT - 1
    uint32_t base;          // Адрес начала таблицы GDT
} __attribute__((packed));

// Инициализация GDT
void gdt_init(void);

// Функция обновления GDT (определена в ассемблере)
extern void gdt_flush(uint32_t);

#endif /* ARCH_I386_GDT_H */