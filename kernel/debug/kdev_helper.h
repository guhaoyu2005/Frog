/*
 *
 *      kdev_helper.h
 *
 *      Copyright (C) 2017 Haoyu Gu
 *
 *
 */

#ifndef KDEV_HELPER_H_
#define KDEV_HELPER_H_

typedef __builtin_va_list va_list;

#define va_start(ap, last)         (__builtin_va_start(ap, last))
#define va_arg(ap, type)           (__builtin_va_arg(ap, type))
#define va_end(ap) 

#include "types.h"

typedef enum {
    cc_black = 0,
    cc_blue = 1,
    cc_green = 2,
    cc_cyan = 3,
    cc_red = 4,
    cc_magenta = 5,
    cc_brown = 6,
    cc_light_grey = 7,
    cc_dark_grey = 8,
    cc_light_blue = 9,
    cc_light_green = 10,
    cc_light_cyan = 11,
    cc_light_red = 12,
    cc_light_magenta = 13,
    cc_light_yellow  = 14,
    cc_white = 15
} char_color_t;


//out, write byte
void outwb(uint16_t port, uint8_t value);
//in, read byte
uint8_t inrb(uint16_t port);
//in, read word
uint16_t inrw(uint16_t port);

//clear screen
void console_clear();
void console_putc_color(char c, char_color_t back, char_color_t fore);
void console_write(char *cstr);
void console_putc(char c);
void console_write_rev(char *cstr);
void console_write_color(char *cstr, char_color_t back, char_color_t fore);
void console_write_hex(uint32_t n, char_color_t back, char_color_t fore);
void console_write_dec(uint32_t n, char_color_t back, char_color_t fore);

void kprint(char *msg);
void kprint_panic(char *title, char *msg);
void kprint_good(char *title, char *msg);
void kscreen_clear();


void memset(void*, uint32_t, uint32_t); //begin value size
void memcpy(void*, const void*, uint32_t);  //dest src size
char *strcpy(char*, const char*);  // dest src  (r dest)
char *strcat(char*, const char*);  //dest src   (r dest)
int strlen(char*);
int strcmp(const char *, const char *);


#endif  //KDEV_HELPER_H_
