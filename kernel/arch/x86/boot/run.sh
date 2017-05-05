#!/bin/sh
rm -f boot.bin
./build.sh
printf "Running...\n"
qemu-system-x86_64 -drive format=raw,file=boot
