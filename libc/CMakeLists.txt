# Определение исходных файлов для libc
set(LIBC_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/string.c
        ${CMAKE_CURRENT_SOURCE_DIR}/stdio.c
)

# Создание статической библиотеки libc
add_library(c STATIC ${LIBC_SOURCES})

# Добавление пути для заголовочных файлов
target_include_directories(c PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)