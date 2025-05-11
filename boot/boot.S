/* Multiboot заголовок */
.set ALIGN,    1<<0             /* выравнивание загруженных модулей по границам страниц */
.set MEMINFO,  1<<1             /* предоставление карты памяти */
.set FLAGS,    ALIGN | MEMINFO  /* флаги для Multiboot */
.set MAGIC,    0x1BADB002       /* магическое число для идентификации заголовка */
.set CHECKSUM, -(MAGIC + FLAGS) /* контрольная сумма */

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Стек */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

/* Точка входа */
.section .text
.global _start
.type _start, @function
_start:
    /* Установка стека */
    movl $stack_top, %esp

    /* Вызов основной функции ядра */
    call kernel_main

    /* Если ядро вернется, входим в бесконечный цикл */
    cli                  /* Выключаем прерывания */
1:  hlt                  /* Останавливаем процессор */
    jmp 1b               /* Если произойдет NMI, прыгаем обратно в hlt */

/* Размер _start */
.size _start, . - _start