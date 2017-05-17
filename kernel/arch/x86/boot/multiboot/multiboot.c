#include "multiboot.h"
#ifdef K_DEV
#include "kdev_helper.h"
#endif

elf_t elf_from_multiboot(multiboot_t *multiboot) {
    elf_t elf;
    elf_section_header_t *elf_sect_header = multiboot->addr;
    uint32_t sect_header_str = multiboot[multiboot->shndx].addr;

    int i;
    for (i=0; i<multiboot->num; i++) {
        const char *name = (const char *)(sect_header_str + elf_sect_header[i].name);
        if (strcmp(name, ".strtab") == 0) {
            elf.strtab = (const char *)elf_sect_header[i].addr;
            elf.strtabsz = elf_sect_header[i].size;
        }
        if (strcmp(name, ".symtab") == 0) {
            elf.symtab = (elf_symbol_t*)elf_sect_header[i].addr;
            elf.symtabsz = elf_sect_header[i].size;
        }
    }
    return elf;
}

const char *elf_get_symbol(uint32_t addr, elf_t *elf) {
    int i;
    for (i = 0; i < (elf->symtabsz / sizeof(elf_symbol_t)); i++) {
        if (ELF32_ST_TYPE(elf->symtab[i].info) != ELF_STB_WEAK) {
              continue;
        }
        if ( (addr >= elf->symtab[i].value) && (addr < (elf->symtab[i].value + elf->symtab[i].size)) ) {
            return (const char *)((uint32_t)elf->strtab + elf->symtab[i].name);
        }
    }

    return NULL;
}