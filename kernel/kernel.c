#include <arch/i386/cpu.h>
#include <arch/i386/gdt.h>
#include <arch/i386/idt.h>
#include <arch/i386/isr.h>
#include <arch/i386/tty.h>
#include <arch/i386/timer.h>
#include <arch/i386/keyboard.h>

// Основная функция ядра
void kernel_main(void) {
    // Инициализация терминала
    terminal_initialize();
    terminal_writestring("=== POSIX-like OS for i386 ===\n");
    terminal_writestring("Initializing kernel...\n");

    // Определение CPU
    cpu_detect();
    terminal_writestring("CPU Vendor: ");
    terminal_writestring(cpu_get_vendor());
    terminal_writestring("\n");

    // Инициализация GDT
    terminal_writestring("Initializing GDT...\n");
    gdt_init();

    // Инициализация IDT
    terminal_writestring("Initializing IDT...\n");
    idt_init();

    // Инициализация ISR
    terminal_writestring("Initializing ISR...\n");
    isr_init();

    // Инициализация таймера (100 Гц)
    terminal_writestring("Initializing System Timer...\n");
    timer_init(100);

    // Инициализация клавиатуры
    terminal_writestring("Initializing Keyboard...\n");
    keyboard_init();

    terminal_writestring("\nSystem initialized successfully!\n");
    terminal_writestring("Welcome to POSIX-like OS!\n\n");

    // Основной цикл обработки
    for (;;) {
        // Приостанавливаем процессор до следующего прерывания
        __asm__ volatile("hlt");
    }
}