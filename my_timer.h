#ifndef MY_TIMER_H
#define MY_TIMER_H

#include "FreeRTOS.h"

void timer_init();
void timer_start();
uint32_t get_current_tick();

#endif