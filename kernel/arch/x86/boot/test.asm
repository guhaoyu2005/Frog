org 0x1000
    mov dx,03d4h;03d4h是索引端口
mov al,0eh;内部的0eh位置存放着光标位置的高八位
out dx,al
inc dx
in al,dx
mov bh,al
 
dec dx
mov al,0fh
out  dx,al
inc dx
in al,dx
mov bl,al
 
    inc bx
    inc bx
 
mov  dx,03d4h
mov al,0eh
out dx,al
inc dx
mov al,bh
out dx,al
 
dec dx
mov al,0fh;写入光标位置低八位
out dx,al
inc dx
mov al,bl
out dx,al