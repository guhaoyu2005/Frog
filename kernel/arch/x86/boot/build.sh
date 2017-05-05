#!/bin/sh
printf "Cleaning up...\n"
if [ -f "*.bin" ] ; then
    rm -f *.bin
fi
printf "Building...\n"
nasm -o boot boot.asm
printf "Done.\n"
