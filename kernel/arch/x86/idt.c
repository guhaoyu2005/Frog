/*
 *
 *      idt.c
 *
 *      Copyright (C) 2017 Haoyu Gu
 *
 *
 */
#ifdef K_DEV
#include "kdev_helper.h"
#endif
#include "idt.h"

extern void idt_flush(uint32_t);

void reg_interrupt_handler(uint8_t ir_n, interrupt_handler_t hl) {
    interrupt_handler[ir_n] = hl;
}

void isr_handler(pt_regs *regs) {
    if (interrupt_handler[regs->int_no]) {
        interrupt_handler[regs->int_no](regs);
    }
    else {
        kprint("Unhandled Interrupt.\n");
    }
}

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_entry[num].base_lo = base & 0xffff;
    idt_entry[num].base_hi = (base >> 16) & 0xffff;
    
    idt_entry[num].sel = sel;
    idt_entry[num].always0 = 0;

    idt_entry[num].flags = flags;
}

void init_idt() {
    /*
    //check CPUID for apic availablity
    uint32_t cpuid = 0;
    asm volatile(".intel_syntax noprefix\n"
                 "add esp, 4\n"
                 "mov eax, 1\n"
                 "mov %0, edx\n"
                 "ret\n"
                 ".att_syntax prefix"
                 :"=a" (cpuid)
                 :
                 :);
    
    if ( ! (cpuid & (uint32_t)1<<9)) {
        kprint_good("  OK  ", "i8259 used.\n");
    }
    else {
        //apic
        kprint_good("  OK  ", "APIC used.\n");
    }
    kprint("Warning! Incompleted kernel APIC code.\n");
    */
    
    
    //then we init i8259
    //init pri, slave
    outwb(0x20, 0x11);
    outwb(0xA0, 0x11);
    //pri start with 0x20h(32)
    outwb(0x21, 0x20);
    //slave start with 0x28h(40)
    outwb(0xA1, 0x28);
    
    outwb(0x21, 0x04);
    outwb(0xA1, 0x02);
    
    outwb(0x21, 0x01);
    outwb(0xA1, 0x01);
    
    outwb(0x21, 0x0);
    outwb(0xA1, 0x0);
    
    memset(&interrupt_handler, 0, sizeof(interrupt_handler_t)*k_IDT_LENGTH);
    memset(&idt_entry, 0, sizeof(idt_entry_t) * k_IDT_LENGTH);
    idt_ptr.limit = sizeof(idt_entry_t) * k_IDT_LENGTH - 1;
    idt_ptr.base = (uint32_t)&idt_entry;

    idt_set_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
    idt_set_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
    idt_set_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
    idt_set_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
    idt_set_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
    idt_set_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
    idt_set_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
    idt_set_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
    idt_set_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
    idt_set_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
    idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);
    
    idt_set_gate(128, (uint32_t)isr128, 0x08, 0x8E);
    
    idt_flush((uint32_t)&idt_ptr);

    return;
}

void irq_handler(pt_regs *regs) {
    //send handled signal back
    //8259 method
	if (regs->int_no >= 40) {
		//send to slave
		outwb(0xA0, 0x20);
	}
    //send to pri
	outwb(0x20, 0x20);

    if (interrupt_handler[regs->int_no]) {
        interrupt_handler[regs->int_no](regs);
    }
}

