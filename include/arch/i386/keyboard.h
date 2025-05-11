#ifndef ARCH_I386_KEYBOARD_H
#define ARCH_I386_KEYBOARD_H

#include <stdint.h>

// Порты клавиатуры
#define KBD_DATA_PORT   0x60
#define KBD_STATUS_PORT 0x64
#define KBD_COMMAND_PORT 0x64

// Скан-коды клавиш
#define KEY_ESCAPE      0x01
#define KEY_BACKSPACE   0x0E
#define KEY_TAB         0x0F
#define KEY_ENTER       0x1C
#define KEY_CTRL        0x1D
#define KEY_LSHIFT      0x2A
#define KEY_RSHIFT      0x36
#define KEY_ALT         0x38
#define KEY_CAPSLOCK    0x3A
#define KEY_F1          0x3B
#define KEY_F2          0x3C
#define KEY_F3          0x3D
#define KEY_F4          0x3E
#define KEY_F5          0x3F
#define KEY_F6          0x40
#define KEY_F7          0x41
#define KEY_F8          0x42
#define KEY_F9          0x43
#define KEY_F10         0x44
#define KEY_NUMLOCK     0x45
#define KEY_SCROLLLOCK  0x46
#define KEY_HOME        0x47
#define KEY_UP          0x48
#define KEY_PAGEUP      0x49
#define KEY_LEFT        0x4B
#define KEY_CENTER      0x4C
#define KEY_RIGHT       0x4D
#define KEY_END         0x4F
#define KEY_DOWN        0x50
#define KEY_PAGEDOWN    0x51
#define KEY_INSERT      0x52
#define KEY_DELETE      0x53

// Инициализация клавиатуры
void keyboard_init(void);

// Получение ASCII-символа из скан-кода
char keyboard_scancode_to_ascii(uint8_t scancode);

#endif /* ARCH_I386_KEYBOARD_H */