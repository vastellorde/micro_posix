# Добавление подкаталога для архитектурно-зависимого кода
add_subdirectory(arch/i386)

# Определение исходных файлов ядра
set(KERNEL_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/kernel.c
)

# Создание исполняемого файла ядра
add_executable(kernel ${KERNEL_SOURCES})

# Привязка загрузчика и архитектурно-зависимого кода
target_link_libraries(kernel
        boot
        i386_arch
        c
)

# Генерация информации о двоичном файле
add_custom_command(TARGET kernel POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:kernel> $<TARGET_FILE:kernel>.bin
        COMMAND ${CMAKE_OBJDUMP} -S $<TARGET_FILE:kernel> > $<TARGET_FILE:kernel>.lst
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:kernel>
        COMMENT "Creating kernel binary image and size information"
)