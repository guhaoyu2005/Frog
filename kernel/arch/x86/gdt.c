#include "gdt.h"

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
