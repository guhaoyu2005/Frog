    ;; frog/src/boot/boot.asm
    ;;
    ;; Copyright (C) 2017 Haoyu Gu
    ;;
section .data
    KERNEL_SECT db 

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
    
    jmp     GO_P_MODE
    ;; next, we will load the kernel to 0x10000
    LOADER_MSG db "Frog Loader Ver 0.1"
    xor     ax, ax
    
    
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
   
    ret
LOAD_SECOND_STAGE_LOADER:
    call    LOAD_TADPOLE
    jmp     $
    times   510-($-$$) db 0
    dw      0xaa55
    