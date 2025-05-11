#ifndef ARCH_I386_TIMER_H
#define ARCH_I386_TIMER_H

#include <stdint.h>

// Константы для PIT (Programmable Interval Timer)
#define PIT_FREQ      1193182   // Частота PIT (1.193182 МГц)
#define PIT_COMMAND   0x43      // Порт регистра команд PIT
#define PIT_DATA      0x40      // Порт данных канала 0 PIT

// Инициализация таймера с заданной частотой
void timer_init(uint32_t frequency);

// Получение текущего тика таймера
uint32_t timer_get_ticks(void);

// Задержка на указанное число тиков
void timer_wait(uint32_t ticks);

// Задержка на указанное число миллисекунд
void timer_sleep(uint32_t milliseconds);

#endif /* ARCH_I386_TIMER_H */