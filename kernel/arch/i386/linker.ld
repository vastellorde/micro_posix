/* Точка входа - символ _start из boot.S */
ENTRY(_start)

/* Схема секций в памяти */
SECTIONS
{
    /* Начинаем с 1 мегабайта - типичная точка загрузки для i386 */
    . = 1M;

    /* Сначала секция .text с мультизагрузочным заголовком */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* Данные только для чтения */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Инициализированные данные */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* Неинициализированные данные */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /* Конец ядра */
    . = ALIGN(4K);
    end = .;
}