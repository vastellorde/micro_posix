.section .text
.global gdt_flush
.type gdt_flush, @function

gdt_flush:
    # Загрузка GDT
    movl 4(%esp), %eax   # Получаем аргумент (указатель на GDT)
    lgdt (%eax)          # Загружаем GDT

    # Обновляем сегментные регистры
    movw $0x10, %ax      # 0x10 - смещение в GDT для сегмента данных
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    # Дальний переход для обновления CS
    ljmp $0x08, $flush   # 0x08 - смещение в GDT для сегмента кода
flush:
    ret