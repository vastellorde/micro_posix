#!/bin/bash

# Путь к ядру
KERNEL="cmake-build-debug/kernel/kernel"

# Проверка существования файла
if [ ! -f "$KERNEL" ]; then
    echo "Kernel not found: $KERNEL"
    exit 1
fi

# Запуск с QEMU
qemu-system-i386 -kernel "$KERNEL" -serial stdio -monitor none