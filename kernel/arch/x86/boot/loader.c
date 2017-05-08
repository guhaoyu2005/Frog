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

#define k_MEM_GDT_LENGTH  5

//flat-mode
typedef struct gdt_entry_t {
    uint16_t limit_low;
    uint16_t base_low;  //total 32 bit = l+m+h
    uint8_t  base_middle;
    uint8_t  access; // 8-15  4type 1s 2dpl 1p
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;  //we don't want padding

typedef struct gdt_ptr_t {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

gdt_entry_t gdt_entries[k_MEM_GDT_LENGTH];
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low     = (base & 0xFFFF);
    gdt_entries[num].base_middle  = (base >> 16) & 0xFF;
    gdt_entries[num].base_high    = (base >> 24) & 0xFF;
    
    gdt_entries[num].limit_low    = (limit & 0xFFFF);
    gdt_entries[num].granularity  = (limit >> 16) & 0x0F;
    
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access       = access;
}

void init_gdt() {
    gdt_ptr.limit = sizeof(gdt_entry_t) * k_MEM_GDT_LENGTH - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;
    
    //flat-mode
    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    asm volatile (".intel_syntax noprefix\n"
                  "add esp, 4\n"
                  "mov eax, %0\n"
                  "lgdt [eax]\n"
                  "mov ax, 0x10\n"
                  "mov ds, ax\n"
                  "mov es, ax\n"
                  "mov fs, ax\n"
                  "mov gs, ax\n"
                  "mov ss, ax\n"
                  "jmp 0x08:flush\n"
                  "flush:\n"
                  "ret\n"
                  ".att_syntax prefix"
                  :
                  :"r" ((uint32_t)&gdt_ptr)
                  :);
}


int loader_entry()
{
    init_gdt();
    
    kscreen_clear();
    kprint_good("Good  ", "Loader loaded.\n");
    kprint_good("Good  ", "GDT initialized.\n");
    kprint_panic("Fatal ", "Kernel does not exist!");
    while (1) {
    }
    return 0;
}



