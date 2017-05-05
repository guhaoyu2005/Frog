/*
  /boot/boot.c

  Copyright (C) 2017 Haoyu Gu

  This is the second stage loader which run under protect-mode

 */

asm ("jmp start");

void start() {
    /*
    volatile char *videoMem = (volatile char*)0xb8000;
    const char *string = "Loaded!";
    int color = 7;
    while (*string != 0) {
        *videoMem++ = *string++;
        *videoMem++ = color;
    }
     */
    while (1) {
        
    }
}
