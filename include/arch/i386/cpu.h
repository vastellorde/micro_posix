#ifndef ARCH_I386_CPU_H
#define ARCH_I386_CPU_H

#include <stdint.h>

// Функции ввода-вывода
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void io_wait(void) {
    outb(0x80, 0); // Порт 0x80 используется для задержки на шине ввода-вывода
}

// Управление прерываниями
static inline void cli(void) {
    __asm__ volatile("cli");
}

static inline void sti(void) {
    __asm__ volatile("sti");
}

static inline void hlt(void) {
    __asm__ volatile("hlt");
}

// Получение состояния флагов
static inline uint32_t get_eflags(void) {
    uint32_t eflags;
    __asm__ volatile("pushfl; popl %0" : "=r"(eflags));
    return eflags;
}

// Функция задержки
void delay(uint32_t milliseconds);

// Получение информации о CPU
void cpu_detect(void);
const char* cpu_get_vendor(void);

#endif /* ARCH_I386_CPU_H */