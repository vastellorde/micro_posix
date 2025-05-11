set(BOOT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/boot.S
        ${CMAKE_CURRENT_SOURCE_DIR}/init.c
)

# Создание статической библиотеки для загрузчика
add_library(boot STATIC ${BOOT_SOURCES})

# Добавление зависимостей
target_link_libraries(boot PRIVATE i386_arch c)