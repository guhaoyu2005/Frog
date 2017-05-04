#!/bin/sh
if ! [ -f "boot.bin" ] ; then
    ./build.sh
fi
printf "Running...\n"
qemu-system-x86_64 -drive format=raw,file=boot
