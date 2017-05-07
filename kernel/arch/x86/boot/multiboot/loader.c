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

int loader_entry()
{
    kscreen_clear();
    kprint_good("Good ", "Loader loaded.\n");
    kprint_panic("Fatal ", "Kernel does not exist!");
    return 0;
}
