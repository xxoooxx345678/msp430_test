#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdint.h>

double fram_latency_read(uint32_t read_cnt);

double fram_latency_write(uint32_t write_cnt);

void nand_test();

double nand_latency_read(uint32_t read_cnt);

double nand_latency_write(uint32_t write_cnt);

double nand_latency_erase(uint32_t erase_cnt);

#endif
