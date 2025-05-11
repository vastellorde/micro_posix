cmake_minimum_required(VERSION 3.10)

# Определяем кросс-компиляцию
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i386)

# Устанавливаем i386-elf-gcc toolchain
set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_ASM_COMPILER i686-elf-gcc)
set(CMAKE_OBJCOPY i686-elf-objcopy)
set(CMAKE_SIZE i686-elf-size)

# Выключаем тестирование компилятора
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Запуск проекта
project(micro_posix C ASM)

# Флаги компиляции для i386
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-stack-protector -nostdlib")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -m32 -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32 -nostdlib -T ${CMAKE_SOURCE_DIR}/kernel/arch/i386/linker.ld -lgcc")

# Глобальные директории включений
include_directories(
        ${CMAKE_SOURCE_DIR}/include
)

# Включение субдиректорий
add_subdirectory(boot)
add_subdirectory(kernel)
add_subdirectory(libc)

# Добавление кастомной команды для создания загрузочного образа
add_custom_target(image
        COMMAND ${CMAKE_SOURCE_DIR}/tools/createimage.sh ${CMAKE_BINARY_DIR}/kernel/kernel.bin
        DEPENDS kernel
        COMMENT "Creating bootable image"
)

# Добавление кастомной команды для запуска в QEMU
add_custom_target(run
        COMMAND qemu-system-i386 -kernel ${CMAKE_BINARY_DIR}/kernel/kernel -serial stdio -display none
        DEPENDS kernel
        COMMENT "Running kernel in QEMU"
)

# Добавление кастомной команды для запуска с графикой
add_custom_target(run-gui
        COMMAND qemu-system-i386 -kernel ${CMAKE_BINARY_DIR}/kernel/kernel -serial stdio
        DEPENDS kernel
        COMMENT "Running kernel in QEMU with GUI"
)

# Добавление кастомной команды для отладки
add_custom_target(debug
        COMMAND qemu-system-i386 -kernel ${CMAKE_BINARY_DIR}/kernel/kernel -s -S -serial stdio -display none &
        COMMAND i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file ${CMAKE_BINARY_DIR}/kernel/kernel"
        DEPENDS kernel
        COMMENT "Debugging kernel in QEMU with GDB"
)