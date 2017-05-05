    ;; frog/src/boot/boot.asm
    ;;
    ;; Copyright (C) 2017 Haoyu Gu
    ;;
section .data

section .text
    global	_main
_main:
    ;;  world begins at 0x7c00  <->  0x7dff
    org     0x07c00
    mov     ax, 0003h
    int     10h
    mov     ax, LOADER_MSG
    mov     bp, ax
    mov     cx, 19
    mov     ax, 1301h
    mov     bx, 0007h
    mov     dl, 0
    int     10h
    jmp     DEBUG_LOAD_SE_SECTOR
    ;; next, we will load the kernel to 0x10000
    LOADER_MSG db "Frog Loader Ver 0.1"
DEBUG_LOAD_SE_SECTOR:
    mov     ax, 0
    mov     es, ax
    mov     bx, 0x1000          ;will load to 0x1000
    mov     ah, 02
    mov     al, 01
    mov     ch, 00
    mov     cl, 02              ;read sector 02
    mov     dh, 00
    int     13h
    ;; check error
    or      ah, ah
    jnz     LOAD_ERROR
    ;; will go to 32bit
GO_P_MODE:
    ;; we will switch to protect mode here
    cli                         ;disable interrupts
    lgdt    [gdtr_addr]
    mov     eax, cr0
    or      eax, 1
    mov     cr0, eax            ;set PE in cr0 to 1 for enabling PMode
CLR_PREFETCH_PIPELN_Q:
    jmp     EMPTY_PQ_TRICK
    nop
    nop
EMPTY_PQ_TRICK:                 ;long jump for clearing prefetched instr
    jmp     LOAD_SECOND_STAGE_LOADER
SETUP_GDT:
    ;; copy this from intel x86 ref
gdt_table_start:
gdt_null:
	dd 0h
	dd 0h
	gdt_data_addr equ $-gdt_table_start
gdt_data:
	dw 07ffh
	dw 0h
	db 0h
	db 10010010b
	db 11000000b
	db 0
	gdt_video_addr equ $-gdt_table_start
gdt_video:
	dw 0ffh
	dw 8000h
	db 0bh
	db 10010010b
	db 11000000b
	db 0
	gdt_code_addr equ $-gdt_table_start
gdt_code:
	dw 07ffh
	dw 1h
	db 80h
	db 10011010b
	db 11000000b
	db 0
gdt_table_end:

gdtr_addr:
	dw gdt_table_end-gdt_table_start-1
	dd gdt_table_start

LOAD_TADPOLE:
    jmp     gdt_code_addr:0x1000
    ret
LOAD_SECOND_STAGE_LOADER:
    call    LOAD_TADPOLE
    jmp     $
LOAD_ERROR:
    mov     ah, 02h
    mov     bh, 00h
    mov     dx, 0300h
    int     10h
    mov     ax, LOADER_ERROR_MSG
    mov     bp, ax
    mov     cx, 30
    mov     ax, 1301h
    mov     bx, 0007h
    mov     dl, 0
    int     10h
    jmp     $
    LOADER_ERROR_MSG db "Error! Failed to load kernel."
    times   510-($-$$) db 0
    dw      0xaa55
    