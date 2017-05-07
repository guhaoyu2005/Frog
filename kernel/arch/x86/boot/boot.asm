    ;; frog/src/boot/boot.asm
    ;;
    ;; Copyright (C) 2017 Haoyu Gu
    ;;
    ;; Firstly, the bios will place this tiny piece into 0x7c00
    ;; next, we will move this to 0x9000 (like linux)
    ;; and load the kernel to 0x10000 (from sector 2 for now)
    ;;
    ;;
section .text
    global	_main
_main:
    org     0x07c00
    ;; we will move first
    mov     ax, 0x7c0
    mov     ds, ax
    mov     ax, 0x900
    mov     es, ax
    xor     di, di
    xor     si, si
    mov     cx, 256
    rep     movsw
    jmp     0x9000+MOVED-0x7c00
MOVED:
    mov     ax, cs
    mov     ds, ax
    mov     es, ax
    mov     ss, ax
    mov     ax, 0003h
    int     10h
    mov     ax, LOADER_MSG
    mov     bp, ax
    mov     cx, 19
    mov     ax, 1301h
    mov     bx, 0007h
    push    dx
    mov     dl, 0
    int     10h
    pop     dx
    jmp     DEBUG_LOAD_SE_SECTOR
    ;; next, we will load the loader to 0x1000
    LOADER_MSG db "Frog Loader Ver 0.1"
DEBUG_LOAD_SE_SECTOR:
    mov     ax, 0
    mov     es, ax
    mov     bx, 9200h
    mov     ax, 0201h
    mov     cx, 0002h           ;track sector
    mov     dh, 00h
    int     13h
    jmp     LOAD_TADPOLE
LOAD_TADPOLE:
    jmp     0:0x9200
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
