#ifndef ARCH_I386_ISR_H
#define ARCH_I386_ISR_H

#include <stdint.h>

// Структура для сохранения регистров при прерывании
struct registers {
    uint32_t ds;                                     // Сегмент данных
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Сохраненные регистры PUSHA
    uint32_t int_no, err_code;                       // Номер прерывания и код ошибки
    uint32_t eip, cs, eflags, useresp, ss;           // Сохраненные процессором
} __attribute__((packed));

// Тип для обработчика прерывания
typedef void (*isr_t)(struct registers*);

// Инициализация обработчиков прерываний
void isr_init(void);

// Регистрация обработчика прерывания
void register_interrupt_handler(uint8_t n, isr_t handler);

// Декларации обработчиков прерываний, определенных в ассемблере
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

// IRQ обработчики
extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

#endif /* ARCH_I386_ISR_H */