#ifndef GDT_H_
#define GDT_H_

#define k_MEM_GDT_LENGTH  5
#include "types.h"

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

void gdt_flush(uint32_t);

gdt_entry_t gdt_entries[k_MEM_GDT_LENGTH];
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void init_gdt();

#endif
