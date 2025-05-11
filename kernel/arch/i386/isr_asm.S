# Макросы для обработчиков прерываний

# Обработчик прерывания без кода ошибки
.macro ISR_NOERRCODE num
.global isr\num
.type isr\num, @function
isr\num:
    cli                  # Выключаем прерывания
    pushl $0             # Пустой код ошибки
    pushl $\num          # Номер прерывания
    jmp isr_common_stub
.endm

# Обработчик прерывания с кодом ошибки
.macro ISR_ERRCODE num
.global isr\num
.type isr\num, @function
isr\num:
    cli                  # Выключаем прерывания
    pushl $\num          # Номер прерывания
    jmp isr_common_stub
.endm

# Обработчик IRQ
.macro IRQ num, irqnum
.global irq\num
.type irq\num, @function
irq\num:
    cli                  # Выключаем прерывания
    pushl $0             # Пустой код ошибки
    pushl $\irqnum       # Номер прерывания (32 + IRQ номер)
    jmp irq_common_stub
.endm

# Определяем обработчики прерываний
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

# Определяем обработчики IRQ
IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

# Внешние обработчики
.extern isr_handler
.extern irq_handler

# Общая часть обработчика прерывания
isr_common_stub:
    # Сохраняем регистры
    pusha

    # Сохраняем сегмент данных
    movw %ds, %ax
    pushl %eax

    # Загружаем сегмент ядра
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    # Вызываем обработчик
    call isr_handler

    # Восстанавливаем сегмент данных
    popl %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    # Восстанавливаем регистры
    popa

    # Удаляем номер прерывания и код ошибки
    addl $8, %esp

    # Восстанавливаем прерывания и возвращаемся
    sti
    iret

# Общая часть обработчика IRQ
irq_common_stub:
    # Сохраняем регистры
    pusha

    # Сохраняем сегмент данных
    movw %ds, %ax
    pushl %eax

    # Загружаем сегмент ядра
    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    # Вызываем обработчик
    call irq_handler

    # Восстанавливаем сегмент данных
    popl %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    # Восстанавливаем регистры
    popa

    # Удаляем номер прерывания и код ошибки
    addl $8, %esp

    # Восстанавливаем прерывания и возвращаемся
    sti
    iret