# Определение исходных файлов для i386
set(I386_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/cpu.c
        ${CMAKE_CURRENT_SOURCE_DIR}/gdt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/gdt_asm.S
        ${CMAKE_CURRENT_SOURCE_DIR}/idt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/idt_asm.S
        ${CMAKE_CURRENT_SOURCE_DIR}/isr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/isr_asm.S
        ${CMAKE_CURRENT_SOURCE_DIR}/pic.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tty.c
        ${CMAKE_CURRENT_SOURCE_DIR}/timer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/keyboard.c
)

# Создание статической библиотеки
add_library(i386_arch STATIC ${I386_SOURCES})

# Добавление пути для заголовочных файлов
target_include_directories(i386_arch PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# Указываем явно зависимость
target_link_libraries(i386_arch PRIVATE c)