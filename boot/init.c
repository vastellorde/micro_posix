// Прототип функции ядра
void kernel_main(void);

// Функция инициализации
void init(void) {
    // Просто вызываем основную функцию ядра
    kernel_main();

    // Если ядро вернётся, зацикливаемся
    while (1) {
        __asm__ volatile("hlt");
    }
}