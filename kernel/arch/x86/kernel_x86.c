#include "kernel_x86.h"
#ifdef K_DEV
#include "kdev_helper.h"
#endif
#include "types.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "support.h"
#include "pmm.h"

int timertest = 0;

void foo() {
    //kprint_good("Good  ", "TICK\n");
    //kprint("a");
    timertest++;
    if (timertest >= 20000) {
        kprint_good("Good  ", "+100s !\n");
        timertest = 0;
    }
    return;
}

void init_kernel() {
    kprint_good("Good  ", "Loader loaded.\n");
    
    init_timer(200, &foo);
    asm volatile ("sti");
    
    printk("PRINTK TEST****\nint = %d\nu_int = %u\noct = %o\nhex = %x\nHEX = %X\nchar = %c\nstr = %s\n%%\n", -65534, 65534, 65527, 65527, 65527, 'c', "STRING");
    
    
    printk("Kernel size: %dKB\n", (kernel_end-kernel_begin+1023)/1024);
    printk("0x%x - 0x%x\n", kernel_begin, kernel_end);
    
    view_physical_mem_map();
    
    
    while (1){};
}
