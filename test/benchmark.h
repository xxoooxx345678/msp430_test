#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdint.h>

void test();

double latency_read(uint32_t read_cnt);

double latency_write(uint32_t write_cnt);

double latency_erase(uint32_t erase_cnt);

#endif
