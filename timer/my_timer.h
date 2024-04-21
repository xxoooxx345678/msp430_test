#ifndef MY_TIMER_H
#define MY_TIMER_H

#include "FreeRTOS.h"

void timer_init();
void timer_start();
uint32_t get_current_tick();
double get_elapsed_time(uint32_t start, uint32_t end, uint32_t TIMER_FREQ);

#endif
