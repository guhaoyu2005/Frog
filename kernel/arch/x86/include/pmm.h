#ifndef PMM_H_
#define PMM_H_

#include "multiboot.h"

#define STACK_SIZE 8192
#define PMM_MAX_SIZE 0x80000000 // 2GB
#define PMM_PAGE_SIZE 0x1000  //4K
#define PAGE_MAX_NUM (PMM_MAX_SIZE/PMM_PAGE_SIZE)
#define PHY_PAGE_MASK 0xFFFFF000

extern uint32_t pmm_phy_page_count;

void pmm_init();

uint32_t pmm_alloc_page();
void pmm_free_page(uint32_t);


extern uint8_t kernel_begin[];
extern uint8_t kernel_end[];

void view_physical_mem_map();


#endif
