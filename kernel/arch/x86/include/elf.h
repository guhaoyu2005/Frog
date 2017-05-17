#ifndef ELF_H_
#define ELF_H_

#include "types.h"

#define ELF32_ST_TYPE(info) ((info) & 0xf)

enum ELF_STB {
    ELF_STB_LOCAL = 0x0,
    ELF_STB_GLOBAL = 0X1,
    ELF_STB_WEAK = 0x2,
    ELF_STB_LOOS = 0xa,
    ELF_STB_HIOS = 0xc,
    ELF_STB_LOPROC = 0xd,
    ELF_STB_HIPROC = 0xf
};

typedef struct elf_section_header_t {
    uint32_t name;
    uint32_t type;
    uint32_t flags;
    uint32_t addr;
    uint32_t offset;
    uint32_t size;
    uint32_t link;
    uint32_t info;
    uint32_t addralign;
    uint32_t entsize;
} __attribute__((packed)) elf_section_header_t;

typedef struct elf_symbol_t {
    uint32_t name;
    uint32_t value;
    uint32_t size;
    uint8_t  info;
    uint8_t  other;
    uint16_t shndx;
} __attribute__((packed)) elf_symbol_t;

typedef struct elf_t {
    elf_symbol_t *symtab;
    uint32_t      symtabsz;
    const char   *strtab;
    uint32_t      strtabsz;
} elf_t;

#endif
