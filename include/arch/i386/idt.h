#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H

#include <stdint.h>

// Структура для записи IDT
struct idt_entry {
    uint16_t base_low;      // Младшие биты адреса обработчика (0-15)
    uint16_t selector;      // Селектор сегмента кода
    uint8_t  always0;       // Всегда 0
    uint8_t  flags;         // Флаги
    uint16_t base_high;     // Старшие биты адреса обработчика (16-31)
} __attribute__((packed));

// Структура для указателя IDT
struct idt_ptr {
    uint16_t limit;         // Размер IDT - 1
    uint32_t base;          // Адрес начала таблицы IDT
} __attribute__((packed));

// Инициализация IDT
void idt_init(void);

// Функция установки обработчика прерывания
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

// Функция обновления IDT (определена в ассемблере)
extern void idt_flush(uint32_t);

#endif /* ARCH_I386_IDT_H */