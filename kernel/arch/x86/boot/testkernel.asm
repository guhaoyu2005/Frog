    org 100h
    mov ax, 0b800h
    mov gs, ax
    mov ah, 0fh
    mov al, "O"
    mov [gs:((80*0+39)*2)], ax

    jmp $