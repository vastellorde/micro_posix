#!/bin/bash

BUILD_DIR="build"
KERNEL="${BUILD_DIR}/kernel/kernel"

# Запуск QEMU с настройками для отладки
qemu-system-aarch64 \
    -M virt \
    -cpu cortex-a53 \
    -m 256M \
    -nographic \
    -kernel "$KERNEL" \
    -semihosting \
    -s -S &

QEMU_PID=$!

echo "QEMU started with PID: $QEMU_PID"
echo "Connecting LLDB to localhost:1234..."

# Подготовка скрипта команд для LLDB
cat > lldb_commands.txt << EOF
platform select remote-gdb-server
target create ${KERNEL}
gdb-remote localhost:1234
EOF

# Запуск LLDB с подготовленным скриптом
lldb -s lldb_commands.txt

# Завершение QEMU при выходе из отладчика
kill $QEMU_PID