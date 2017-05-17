#ifndef MULTIBOOT_H_
#define MULTIBOOT_H_

#include "types.h"
#include "elf.h"

typedef struct multiboot_t {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device; 
    uint32_t cmdline; 
    uint32_t mods_count;   
    uint32_t mods_addr;
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr; 
    uint32_t config_table;   
    uint32_t boot_loader_name;
    uint32_t apm_table;         
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint32_t vbe_interface_off;
    uint32_t vbe_interface_len;
}__attribute__((packed)) multiboot_t;

typedef struct mmap_entry_t {
    uint32_t size;
    uint32_t base_addr_low;
    uint32_t base_addr_high;
    uint32_t length_low;
    uint32_t length_high;
    uint32_t type;
}__attribute__((packed)) mmap_entry_t;

extern multiboot_t *glb_mboot_ptr;
elf_t elf_from_multiboot(multiboot_t *);
const char *elf_get_symbol(uint32_t, elf_t *);

#endif
