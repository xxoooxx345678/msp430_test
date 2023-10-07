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

void test()
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

double latency_read(uint32_t read_cnt)
{
    uint32_t elapsed_time = 0;

    set_input();

    uint32_t i;
    uint32_t st, ed;

    for (i = 0; i < read_cnt; ++i)
    {
        write_op(i, 0, input, 2048);
        st = get_current_tick();
        read_op(i, 0, output, 2048);
        ed = get_current_tick();
        elapsed_time += (ed - st);
        volatile int rrr = validate(input, output, 2048);
        if (rrr != (uint16_t)-1)
            printf("READ ERROR: %d %d\n", i, rrr);
    }

    return get_elasped_time(0, elapsed_time, 8000000);
}

double latency_write(uint32_t write_cnt)
{
    uint32_t elapsed_time = 0;

    set_input();

    uint32_t i;
    uint32_t st,ed;

    for (i = 0; i < write_cnt; ++i)
    {
        st = get_current_tick();
        write_op(i, 0, input, 2048);
        ed = get_current_tick();
        elapsed_time += (ed - st);
        read_op(i, 0, output, 2048);
        if (validate(input, output, 2048) != (uint16_t)-1)
            printf("WRITE ERROR: %d\n", i);
    }

    return get_elasped_time(0, elapsed_time, 8000000);
}

double latency_erase(uint32_t erase_cnt)
{
    uint32_t elapsed_time = 0;

    set_input();

    uint32_t i, j;
    uint32_t st, ed;

    for (i = 0; i < erase_cnt; ++i)
    {
        for (j = 0; j < 64; ++j)
            write_op((i<<6)+j, 0, input, 2048);
        st = get_current_tick();
        erase_op((i<<6));
        ed = get_current_tick();
        elapsed_time += (ed - st);
    }

    return get_elasped_time(0, elapsed_time, 8000000);
}
