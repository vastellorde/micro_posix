.section .text
.global idt_flush
.type idt_flush, @function

idt_flush:
    # Загрузка IDT
    movl 4(%esp), %eax   # Получаем аргумент (указатель на IDT)
    lidt (%eax)          # Загружаем IDT
    ret