    ;; frog/src/boot/bs.asm
    ;;
    ;; Copyright (C) 2017 Haoyu Gu
    ;; 
section .data
    BOOT_BASEADDR db 0x07c0
    ;;  MSG_BOOT_LEN  equ $ - MSG_BOOT 

section .text
    global	_main
    
_main:
    ;;  world begins at 0x7c00  <->  0x7dff 
    org     0x7c00
    call    SHOW_INIT_MSG
    jmp     $
CLS_SCR:
    mov     ax, 0x0003
    int     10h
    ret
RESET_CSR:
    mov     ah, 02
    mov     dx, 0x0000
    int     10h
SHOW_INIT_MSG:
    call    CLS_SCR
    mov     ax, MSG_BOOT
    mov     bp, ax
    mov     cx, 15
    mov     ax, 0x1301
    mov     bx, 0x0007
    mov     dl, 0
    int     10h
    mov     ax, 0x0200
    mov     dx, 0x0100
    int     10h
    ret
    MSG_BOOT      db "Frog Loader 0.1", 0
    
    times   510-($-$$) db 0
    dw      0xaa55
    
    
    
    
    
    
    