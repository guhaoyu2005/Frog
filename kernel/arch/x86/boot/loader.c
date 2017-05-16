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

int timertest = 0;

void foo() {
    //kprint_good("Good  ", "TICK\n");
    //kprint("a");
    timertest++;
    if (timertest >= 200) {
        kprint_good("Good  ", "+1s !\n");
        timertest = 0;
    }
    return;
}

int loader_entry() {
    
    init_idt();
    
    init_gdt();
    
    kscreen_clear();
    kprint_good("Good  ", "Loader loaded.\n");
    kprint_good("Good  ", "IDT initialized.\n");
    kprint_good("Good  ", "GDT initialized.\n");
    kprint_panic("Fatal ", "Kernel does not exist!\n");
    
    init_timer(200, &foo);
    asm volatile ("sti");
    
    

    while (1){}

    return 0;
}



