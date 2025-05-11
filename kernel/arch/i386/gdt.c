#include <arch/i386/gdt.h>

// Объявляем GDT
struct gdt_entry gdt_entries[5];
struct gdt_ptr   gdt_ptr;

// Функция для установки записи в GDT
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

// Функция инициализации GDT
void gdt_init(void) {
    // Настраиваем указатель GDT
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    // Установка записей GDT
    // Нулевой дескриптор
    gdt_set_gate(0, 0, 0, 0, 0);
    // Сегмент кода (0x9A: Present, Ring 0, Code, Executable, Readable)
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // Сегмент данных (0x92: Present, Ring 0, Data, Writable)
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // Пользовательский сегмент кода (0xFA: Present, Ring 3, Code, Executable, Readable)
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // Пользовательский сегмент данных (0xF2: Present, Ring 3, Data, Writable)
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // Загрузка GDT
    gdt_flush((uint32_t)&gdt_ptr);
}