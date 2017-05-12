/*
 *
 *      kdev_helper.c
 *
 *      Copyright (C) 2017 Haoyu Gu
 *
 *
 */

#include <kdev_helper.h>

static uint16_t *v_memory = (uint16_t *)0xB8000;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

inline void outwb(uint16_t port, uint8_t value) {
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

inline uint8_t inrb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "Nd" (port));
    return ret;
}

inline uint16_t inrw(uint16_t port) {
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "Nd" (port));
    return ret;
}

static void move_cursor() {
    // 80*25
    uint16_t cursorLocation = cursor_y * 80 + cursor_x;
    outwb(0x3D4, 14);
    outwb(0x3D5, cursorLocation >> 8);
    outwb(0x3D4, 15);
    outwb(0x3D5, cursorLocation);
}

void console_clear() {
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);
    int i;
    for (i=0; i<80*25; i++) {
        v_memory[i] = blank;
    }
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

static void scroll() {
    uint8_t attribute_byte = (0<<4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);
    int i;
    for (i=0; i<80*24; i++) {
        v_memory[i] = v_memory[i+80];
    }
    for (i=80*24; i<80*25; i++) {
        v_memory[i] = blank;
    }
    cursor_y = 24;
    
}

void console_putc_color(char c, char_color_t back, char_color_t fore) {
    uint8_t back_color = (uint8_t)back;
    uint8_t fore_color = (uint8_t)fore;
    uint8_t attribute_byte = (back_color<<4) | (fore_color & 0x0F);
    uint16_t attribute = attribute_byte << 8;
    
    if (c == 0x08 && cursor_x) {
        cursor_x--;
    } else if (c == 0x09) {
        cursor_x = (cursor_x+8) & ~(8-1);
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c >= ' ') {
        v_memory[cursor_y*80 + cursor_x] = c | attribute;
        cursor_x++;
    }
    
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= 25)
            scroll();
    }
    
    move_cursor();
    
}

void console_write(char *cstr) {
    while (*cstr) {
        console_putc_color(*cstr++, cc_black, cc_light_grey);
    }
}

void console_write_color(char *cstr, char_color_t back, char_color_t fore) {
    while (*cstr) {
        console_putc_color(*cstr++, back, fore);
    }
}

void printk(char *msg, ...) {
    
}

void kprint(char *msg) {
    console_write(msg);
}

void kprint_panic(char *title, char *msg) {
    console_write_color(title, cc_black, cc_red);
    console_write(msg);
}

void kprint_good(char *title, char *msg) {
    console_write_color(title, cc_black, cc_green);
    console_write(msg);
}

void kscreen_clear() {
    console_clear();
}

void memset(void* src, uint32_t val, uint32_t len){
    uint32_t* temp = src;
    while (len > 0) {
        *temp++ = val;
        len--;
    }
} //begin value size

void memcpy(void* dest, const void* src, uint32_t len) {
    uint32_t *temp = dest;
    const uint32_t *tempSrc = src;
    while (len > 0) {
        *temp++ = *tempSrc++;
        len--;
    }
    
}  //dest src size

char *strcpy(char* dest, const char* src) {
    uint32_t *temp = dest;
    uint32_t *tempSrc = src;
    do {
        *temp++ = *tempSrc++;
    } while (*tempSrc != 0);
    return dest;
}  // dest src  (r dest)

char *strcat(char* dest, const char* src) {
    uint32_t *temp = dest;
    while (*temp != '\0') {
        temp++;
    }
    do {
        *temp++ = *src++;
    } while (*src != '\0');
    return dest;
}  //dest src   (r dest)

int strlen(char* src) {
    int i = 0;
    while (*src++) {
        i++;
    }
    return i;
}




