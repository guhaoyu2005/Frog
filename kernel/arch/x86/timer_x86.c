/*
 *
 *      timer_x86.c
 *
 *      Copyright (C) 2017 Haoyu Gu
 *
 *
 */
#include "timer_x86.h"
#include "interrupt_x86.h"
#ifdef K_DEV
#include "kdev_helper.h"
#endif
/*
void timer_callback(pt_regs *regs) {
    //callback
    kprint("TICK");
}

void init_timer(uint32_t frequency, void (*callbk)) {
    reg_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = 1193180 / frequency;

    outwb(0x43, 0x36);

    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t hign = (uint8_t)((divisor >> 8) & 0xFF);
    
    outwb(0x40, low);
    outwb(0x40, hign);
}
*/