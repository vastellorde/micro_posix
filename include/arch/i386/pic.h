#ifndef ARCH_I386_PIC_H
#define ARCH_I386_PIC_H

#include <stdint.h>

// Порты для взаимодействия с PIC
#define PIC1        0x20   // IO-базовый адрес для ведущего PIC
#define PIC2        0xA0   // IO-базовый адрес для ведомого PIC
#define PIC1_COMMAND PIC1
#define PIC1_DATA   (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA   (PIC2+1)

// Инициализация PIC
void pic_init(void);

// Отправка сигнала завершения прерывания (EOI) на PIC
void pic_send_eoi(uint8_t irq);

// Установка маски для PIC
void pic_set_mask(uint8_t irq);

// Очистка маски для PIC
void pic_clear_mask(uint8_t irq);

#endif /* ARCH_I386_PIC_H */