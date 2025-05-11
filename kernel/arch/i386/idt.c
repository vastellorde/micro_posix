#include <arch/i386/idt.h>
#include <libc/string.h>

// Объявляем IDT
struct idt_entry idt_entries[256];
struct idt_ptr   idt_ptr;

// Функция для установки обработчика прерывания
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;

    idt_entries[num].selector = selector;
    idt_entries[num].always0 = 0;
    // Пользовательский режим (3) или режим ядра (0)
    idt_entries[num].flags = flags;
}

// Функция инициализации IDT
void idt_init(void) {
    // Настраиваем указатель IDT
    idt_ptr.limit = sizeof(struct idt_entry) * 256 - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    // Очищаем IDT
    memset(&idt_entries, 0, sizeof(struct idt_entry) * 256);

    // Загрузка IDT
    idt_flush((uint32_t)&idt_ptr);
}