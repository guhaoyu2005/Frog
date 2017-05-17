#include "pmm.h"
#include "types.h"
#ifdef K_DEV
#include "kdev_helper.h"
#endif
#include "support.h"

void view_physical_mem_map() {
    uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
    uint32_t mmap_length = glb_mboot_ptr->mmap_length;

    printk("****Memory map****\n");

    mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
    for (mmap = (mmap_entry_t *)mmap_addr; (uint32_t)mmap < mmap_addr + mmap_length; mmap++) {
        printk("0x%X%X\n", (uint32_t)mmap->base_addr_high, (uint32_t)mmap->base_addr_low);
    }
}


void pmm_init() {
    
}

uint32_t pmm_alloc_page() {
    
}

void pmm_free_page(uint32_t loc) {
    
}