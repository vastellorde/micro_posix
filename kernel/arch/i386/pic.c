#include <arch/i386/pic.h>
#include <arch/i386/cpu.h>

// ICW (Initialization Command Words)
#define ICW1_ICW4      0x01    // ICW4 присутствует
#define ICW1_SINGLE    0x02    // Один PIC (не каскад)
#define ICW1_INTERVAL4 0x04    // Таблица векторов: интервал 4
#define ICW1_LEVEL     0x08    // Срабатывание по уровню
#define ICW1_INIT      0x10    // Инициализация

#define ICW4_8086       0x01   // 8086/88 режим
#define ICW4_AUTO       0x02   // Автоматическое завершение
#define ICW4_BUF_SLAVE  0x08   // Буферизация ведомого
#define ICW4_BUF_MASTER 0x0C   // Буферизация ведущего
#define ICW4_SFNM       0x10   // Специально полностью вложенный режим

// Инициализация PIC
void pic_init(void) {
    uint8_t a1, a2;

    // Сохраняем маски
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    // Инициализация в каскадном режиме
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // ICW2: базовые векторы для IRQ
    outb(PIC1_DATA, 0x20);    // IRQ 0-7: 0x20-0x27
    io_wait();
    outb(PIC2_DATA, 0x28);    // IRQ 8-15: 0x28-0x2F
    io_wait();

    // ICW3: настройка каскада
    outb(PIC1_DATA, 0x04);    // Ведомый PIC на IRQ2
    io_wait();
    outb(PIC2_DATA, 0x02);    // Идентификатор ведомого
    io_wait();

    // ICW4: дополнительная информация
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    // Восстанавливаем сохраненные маски
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}

// Отправка сигнала завершения прерывания
void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, 0x20);
    }
    outb(PIC1_COMMAND, 0x20);
}

// Установка маски для PIC
void pic_set_mask(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) | (1 << irq);
    outb(port, value);
}

// Очистка маски для PIC
void pic_clear_mask(uint8_t irq) {
    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
}