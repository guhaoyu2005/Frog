#！Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
ASM_SOURCES = $(shell find . -name "*.asm")
ASM_OBJECTS = $(patsubst %.asm, %.o, $(ASM_SOURCES))

MACRO = -D K_DEV

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector $(MACRO) -I kernel/include -I kernel/arch/x86/include -I kernel/debug 
LD_FLAGS = -T build/scripts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS = -f elf -g -F stabs


all: $(ASM_OBJECTS) $(C_OBJECTS) link make_image

%.o : %.c
	@echo Compiling kernel file $< ...
	$(CC) $(C_FLAGS) $< -o $@

%.o : %.asm
	@echo Compiling ASM file $< ...
	$(ASM) -o $@ $(ASM_FLAGS) $<

link:
	@echo linking...
	$(LD) $(LD_FLAGS) $(ASM_OBJECTS) $(C_OBJECTS) -o loader

.PHONY:clean
clean:
	$(RM) $(ASM_OBJECTS) $(C_OBJECTS) loader

.PHONY:make_image
make_image:
	sudo mount debug/frog.img /mnt/frog
	sudo cp loader /mnt/frog/frog
	sleep 1
	sudo umount /mnt/frog
	cp debug/frog.img frog.img

.PHONY:qemu
qemu:
	qemu-system-x86_64 -drive format=raw,file=debug/frog.img

.PHONY:bochs
bochs:
	bochs -f kernel/arch/x86/boot/bochssrc
