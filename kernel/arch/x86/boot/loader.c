/*
 *
 *      loader.c
 *
 *      Copyright (C) 2017 Haoyu Gu
 *
 *
 */

#ifdef K_DEV
#include "kdev_helper.h"
#endif
#include "types.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "support.h"


int loader_entry() {
    init_gdt();
    init_idt();
    
    kscreen_clear();
    kprint_good("Good  ", "Loader loaded.\n");
    kprint_good("Good  ", "GDT initialized.\n");
    kprint_panic("Fatal ", "Kernel does not exist!");

    while (1){}

    return 0;
}



