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
#include "kernel_x86.h"


int loader_entry() {
    
    init_idt();
    init_gdt();
    
    kscreen_clear();
    
    init_kernel();
    
    asm volatile ("hlt");

    return 0;
}



