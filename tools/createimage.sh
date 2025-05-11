#!/bin/bash

KERNEL_BIN=$1
OUTPUT_IMG="kernel.img"

if [ -z "$KERNEL_BIN" ]; then
    echo "Usage: $0 <kernel-binary>"
    exit 1
fi

# Создание пустого образа
dd if=/dev/zero of=$OUTPUT_IMG bs=512 count=2880

# Копирование ядра в образ
dd if=$KERNEL_BIN of=$OUTPUT_IMG conv=notrunc

echo "Created bootable image $OUTPUT_IMG"