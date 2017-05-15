/*
 *
 *      idt.h
 *
 *      Copyright (C) 2017 Haoyu Gu
 *
 *
 */
#ifndef IDT_H_
#define IDT_H_

#include "types.h"

#define k_IDT_LENGTH 256
#define  IRQ0     32    // timer
#define  IRQ1     33    // keyboard
#define  IRQ2     34    // IRQ9
#define  IRQ3     35    // serial device
#define  IRQ4     36    // serial device
#define  IRQ5     37    // sound card
#define  IRQ6     38    // floppy control
#define  IRQ7     39    // printer control
#define  IRQ8     40    // instant clock
#define  IRQ9     41    // IRQ2
#define  IRQ10    42    // network card
#define  IRQ11    43    // AGP graphic card
#define  IRQ12    44    // PS/2 mouse
#define  IRQ13    45    // co-processor
#define  IRQ14    46    // IDE0 Control
#define  IRQ15    47    // IDE1 Control

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

typedef struct idt_entry_t {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_t {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

typedef struct pt_regs {
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t int_no;
    uint32_t err_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;
} pt_regs;


void irq_handler(pt_regs *regs);

typedef void (*interrupt_handler_t)(pt_regs *);

idt_ptr_t idt_ptr;
idt_entry_t idt_entry[k_IDT_LENGTH];
interrupt_handler_t interrupt_handler[k_IDT_LENGTH];

void isr0();        // 0 #DE divide 0 ex
void isr1();        // 1 #DB debug ex
void isr2();        // 2 NMI
void isr3();        // 3 BP breakpoint ex
void isr4();        // 4 #OF overflow
void isr5();        // 5 #BR overbound - array
void isr6();        // 6 #UD invalid op code
void isr7();        // 7 #NM device unavailable(no math co-processor)
void isr8();        // 8 #DF double fault(with err code)
void isr9();        // 9 co-processor over segment operation
void isr10();       // 10 #TS invalid TSS(with err code)
void isr11();       // 11 #NP invalid segment(with err code)
void isr12();       // 12 #SS stack error(with err code)
void isr13();       // 13 #GP general protection(with err code)
void isr14();       // 14 #PF page fault(with err code)
void isr15();       // 15 CPU preserve
void isr16();       // 16 #MF floating processing unit err
void isr17();       // 17 #AC align check
void isr18();       // 18 #MC machine check
void isr19();       // 19 #XM SIMD floating error

//intel preserve
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

void isr128();


void reg_interrupt_handler(uint8_t, interrupt_handler_t);
void isr_handler(pt_regs *);
void init_idt();

#endif
