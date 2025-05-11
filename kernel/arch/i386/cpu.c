#include <arch/i386/cpu.h>

// Простой счетчик для задержки
void delay(uint32_t milliseconds) {
    // Очень простая реализация без таймера
    // Это просто цикл, который выполняется примерно указанное количество миллисекунд
    // На реальных системах это будет сильно зависеть от частоты процессора
    for (uint32_t i = 0; i < milliseconds * 1000; i++) {
        io_wait();
    }
}

// Информация о процессоре
static char cpu_vendor[13] = {0};

// Получение информации о процессоре с помощью инструкции CPUID
void cpu_detect(void) {
    uint32_t vendor[3];

    __asm__ volatile(
            "cpuid"
            : "=b" (vendor[0]),
    "=d" (vendor[1]),
    "=c" (vendor[2])
            : "a" (0)
            );

    // Копирование строки-идентификатора производителя
    ((uint32_t*)cpu_vendor)[0] = vendor[0];
    ((uint32_t*)cpu_vendor)[1] = vendor[1];
    ((uint32_t*)cpu_vendor)[2] = vendor[2];
    cpu_vendor[12] = '\0';
}

// Возвращает строку с названием производителя процессора
const char* cpu_get_vendor(void) {
    return cpu_vendor;
}