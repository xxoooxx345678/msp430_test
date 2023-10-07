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

void energy_consumption_read_write(uint32_t rw_cnt)
{
    set_input();

    uint32_t i;

    // Set breakpoint 1 here

    volatile uint8_t dummy1 = 123; // for breakpoint

    for (i = 0; i < rw_cnt; ++i)
        write_op(i, 0, input, PAGE_SIZE);

    // Set breakpoint 2 here

    volatile uint8_t dummy2 = 123; // for breakpoint

    for (i = 0; i < rw_cnt; ++i)
        read_op(i, 0, output, PAGE_SIZE);

    // Set breakpoint 3 here
    return;
}
