#include <arch/i386/timer.h>
#include <arch/i386/cpu.h>
#include <arch/i386/isr.h>
#include "libc/stdio.h"

static uint32_t tick = 0;
static uint32_t frequency = 0;

// Обработчик прерывания от таймера
static void timer_callback(struct registers* regs) {
    tick++;

    // Раскомментируйте, если нужно отображать тики
    // if (tick % frequency == 0) {
    //     printf("One second has passed: %u ticks\n", tick);
    // }

    // Для подавления предупреждения компилятора о неиспользуемом параметре
    (void)regs;
}

// Инициализация таймера с заданной частотой
void timer_init(uint32_t freq) {
    // Регистрация обработчика прерывания
    register_interrupt_handler(IRQ0, &timer_callback);

    // Сохраняем частоту
    frequency = freq;

    // Вычисляем делитель для PIT
    uint32_t divisor = PIT_FREQ / freq;

    // Отправляем команду в PIT
    // 0x36 = 00110110
    // - канал 0
    // - режим 3 (прямоугольная волна)
    // - режим доступа: младший байт, затем старший
    // - режим счета: двоичный
    outb(PIT_COMMAND, 0x36);

    // Отправляем делитель
    outb(PIT_DATA, divisor & 0xFF);       // Младший байт
    outb(PIT_DATA, (divisor >> 8) & 0xFF); // Старший байт
}

// Получение текущего тика таймера
uint32_t timer_get_ticks(void) {
    return tick;
}

// Задержка на указанное число тиков
void timer_wait(uint32_t ticks) {
    uint32_t end_tick = tick + ticks;
    while (tick < end_tick) {
        // Приостанавливаем процессор до следующего прерывания
        __asm__ volatile("hlt");
    }
}

// Задержка на указанное число миллисекунд
void timer_sleep(uint32_t milliseconds) {
    // Вычисляем, сколько тиков нужно ждать
    uint32_t ticks = milliseconds * frequency / 1000;
    if (ticks == 0) ticks = 1; // Минимум 1 тик

    timer_wait(ticks);
}