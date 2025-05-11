#include <arch/i386/keyboard.h>
#include <arch/i386/cpu.h>
#include <arch/i386/isr.h>
#include <arch/i386/tty.h>
#include "libc/stdio.h"

// Флаги состояния клавиатуры
static uint8_t shift_pressed = 0;
static uint8_t caps_lock = 0;

// Таблица преобразования скан-кодов в ASCII без Shift
static char scancode_to_ascii_table[] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
        0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
        '*', 0, ' ', 0
};

// Таблица преобразования скан-кодов в ASCII с Shift
static char scancode_to_ascii_shift_table[] = {
        0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
        '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
        0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
        0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
        '*', 0, ' ', 0
};

// Обработчик прерывания от клавиатуры
static void keyboard_callback(struct registers* regs) {
    // Получение скан-кода клавиши
    uint8_t scancode = inb(KBD_DATA_PORT);

    // Обработка клавиш модификаторов
    if (scancode == KEY_LSHIFT || scancode == KEY_RSHIFT) {
        shift_pressed = 1;
    } else if (scancode == KEY_LSHIFT + 0x80 || scancode == KEY_RSHIFT + 0x80) {
        // 0x80 добавляется к скан-коду при отпускании клавиши
        shift_pressed = 0;
    } else if (scancode == KEY_CAPSLOCK) {
        caps_lock = !caps_lock;
    } else if (!(scancode & 0x80)) { // Если клавиша нажата (не отпущена)
        // Преобразуем скан-код в ASCII
        char ascii = keyboard_scancode_to_ascii(scancode);
        if (ascii) {
            terminal_putchar(ascii);
        }
    }

    // Для подавления предупреждения компилятора о неиспользуемом параметре
    (void)regs;
}

// Инициализация клавиатуры
void keyboard_init(void) {
    // Регистрация обработчика прерывания
    register_interrupt_handler(IRQ1, &keyboard_callback);
}

// Получение ASCII-символа из скан-кода
char keyboard_scancode_to_ascii(uint8_t scancode) {
    // Проверяем, что скан-код находится в пределах таблицы
    if (scancode >= sizeof(scancode_to_ascii_table)) {
        return 0;
    }

    // Выбираем таблицу в зависимости от состояния Shift
    char ascii;
    if (shift_pressed) {
        ascii = scancode_to_ascii_shift_table[scancode];
    } else {
        ascii = scancode_to_ascii_table[scancode];
    }

    // Обработка CapsLock для букв
    if (caps_lock) {
        if (ascii >= 'a' && ascii <= 'z') {
            ascii = ascii - 'a' + 'A';
        } else if (ascii >= 'A' && ascii <= 'Z') {
            ascii = ascii - 'A' + 'a';
        }
    }

    return ascii;
}