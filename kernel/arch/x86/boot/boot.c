/*
  /boot/boot.c

  Copyright (C) 2017 Haoyu Gu

  This is the second stage loader which run under protect-mode

 */

void tadpole_init(void);

void tadpole_init(void) {
    __asm__("mov %ax, 0x0003"
            "int 10h");
    
}
