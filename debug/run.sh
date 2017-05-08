#!/bin/sh
printf "Running...\n"
#bochs
qemu-system-x86_64 -fda ./frog.img
