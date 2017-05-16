/*
 *
 *      timer.h
 *
 *      Copyright (C) 2017 Haoyu Gu
 *
 *
 */
#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include "types.h"

void init_timer(uint32_t frequency, void (*callbk)());
 
#endif
