#include "FreeRTOS.h"
#include "driverlib.h"
#include "benchmark.h"
#include "spi_nand.h"
#include "my_timer.h"
#include "task.h"
#include <stdio.h>

#pragma PERSISTENT(input)
#pragma NOINIT(output)
uint8_t input[2048] = {0};
uint8_t output[2048];

#pragma PERSISTENT(fram_buffer)
volatile uint16_t fram_buffer[32] = {0};

volatile uint16_t sram_buffer[32];

static void set_input()
{
    volatile uint16_t i;

    for (i = 0; i < 2048; ++i)
        input[i] = i % 4;
}

static uint16_t validate(uint8_t *input, uint8_t *output, size_t len)
{
    volatile uint16_t i;
    for (i = 0; i < len; ++i)
        if (input[i] != output[i])
            return i;

    return -1;
}

extern void framRead();
extern void framWrite();

double fram_latency_read(uint32_t read_cnt)
{
    volatile uint32_t i;
 
    for (i = 0; i < 32; ++i)
        fram_buffer[i] = i;
 
    volatile uint32_t st, ed;
    volatile uint32_t tmp = (read_cnt / 2) / 8192;

    volatile uint32_t elapsed_time = 0;

    __no_operation();
//    st = get_current_tick();

    for (i = 0; i < tmp; ++i)
        framRead(); 

//    ed = get_current_tick();
//    elapsed_time += (ed - st);
    __no_operation();
    return get_elasped_time(0, elapsed_time, 8000000) / read_cnt;
}

double fram_latency_write(uint32_t write_cnt)
{
    volatile uint32_t i;
    volatile uint32_t st, ed;
    volatile uint32_t tmp = (write_cnt / 2) / 8192;

    volatile uint32_t elapsed_time = 0;

    __no_operation(); //
//    st = get_current_tick();

    for (i = 0; i < tmp; ++i)
        framWrite();

//    ed = get_current_tick();
//    elapsed_time += (ed - st);
    __no_operation();
    return get_elasped_time(0, elapsed_time, 8000000) / write_cnt;
}

void nand_test()
{
    set_input();

    write_op(0x1694, 0, input, 2048);

    read_op(0x1694, 0, output, 2048);

    uint16_t val = validate(input, output, 2048);

    if (val == (uint16_t)-1)
        printf("read write success\n");
    else
        printf("read write failed at %d\n", val);

    erase_op(0x1692);

    read_op(0x1694, 0, output, 2048);

    clear_all_blocks();
}

double nand_latency_read(uint32_t read_cnt)
{
    uint32_t elapsed_time = 0;

    set_input();

    uint32_t i;
    uint32_t st, ed;

    st = get_current_tick();
    __no_operation();
    for (i = 0; i < read_cnt; ++i)
    {
        read_op(i, 0, output, 2048);
    }
    ed = get_current_tick();
    elapsed_time += (ed - st);
    __no_operation();
    return get_elasped_time(0, elapsed_time, 8000000) / read_cnt;
}

double nand_latency_write(uint32_t write_cnt)
{
    uint32_t elapsed_time = 0;

    set_input();

    uint32_t i;
    uint32_t st, ed;

    st = get_current_tick();
    __no_operation();
    for (i = 0; i < write_cnt; ++i)
    {
        write_op(i, 0, input, 2048);
    }
    ed = get_current_tick();
    elapsed_time += (ed - st);
    __no_operation();

    return get_elasped_time(0, elapsed_time, 8000000) / write_cnt;
}

double nand_latency_erase(uint32_t erase_cnt)
{
    uint32_t elapsed_time = 0;

    set_input();

    uint32_t i, j;
    uint32_t st, ed;

    for (i = 0; i < erase_cnt; ++i)
    {
        for (j = 0; j < 64; ++j)
            write_op((i << 6) + j, 0, input, 2048);
        st = get_current_tick();
        erase_op((i << 6));
        ed = get_current_tick();
        elapsed_time += (ed - st);
    }

    return get_elasped_time(0, elapsed_time, 8000000) / erase_cnt;
}
