#include "FreeRTOS.h"
#include "task.h"
#include "checkpoint.h"
#include <stdio.h>
#include "spi_nand.h"

#define WITH_NAND_FLASH

#pragma PERSISTENT(shutdown_test)
uint8_t shutdown_test = 3;

#pragma NOINIT(undo_log)
uint32_t undo_log[128];
#pragma PERSISTENT(undo_log_ptr)
uint8_t undo_log_ptr = 0;

#pragma PERSISTENT(input)
#pragma NOINIT(output)
uint8_t input[2048] = {0};
uint8_t output[2048];
static void set_input(int key);


void test_main(void);
static void test_print(void *pvParameters);
static void test_nand(void *pvParameters);

void test_main(void)
{
#ifdef WITH_NAND_FLASH
    xTaskCreate(test_nand, "test", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
#elif
    xTaskCreate(test_print, "test", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
#endif

    vTaskStartScheduler();
}

static void test_print(void *pvParameters)
{
    (void)pvParameters;
    volatile int i;
    for (i = 0; i <= 100; ++i)
    {
        printf("i: %d\n", i);
        if (i == 10)
        {
            printf("\n\ncheckpoint at: %d\n\n", i);
            checkpoint();
        }
        else if (i == 20 && shutdown_test == 3)
        {
            shutdown_test--;
            vPortShutdown();
            printf("it shouldn't be printed.\n");
        }
        else if (i == 30)
        {
            printf("\n\ncheckpoint at: %d\n\n", i);
            checkpoint();
        }
        else if (i == 50 && shutdown_test == 2)
        {
            shutdown_test--;
            vPortShutdown();
            printf("it shouldn't be printed.\n");
        }
        else if (i == 80)
        {
            printf("\n\ncheckpoint at: %d\n\n", i);
            checkpoint();
        }
        else if (i == 99 && shutdown_test == 1)
        {
            shutdown_test--;
            vPortShutdown();
            printf("it shouldn't be printed.\n");
        }
    }

    for (;;)
        ;
}

static void set_input(int key) // TODO: randomise assigning value
{
    uint16_t i;

    for (i = 0; i < 2048; ++i)
        input[i] = key;
}

static uint16_t validate(uint8_t *in, uint8_t *out, size_t len)
{
    uint16_t i;
    for (i = 0; i < len; ++i)
        if (in[i] != out[i])
            return i;

    return -1;
}

static void test_nand(void *pvParameters)
{
    cs_drive_high();
    volatile int ret = spi_nand_init();

    if (ret != 0)
        return;

    /* Basic functionality check */

    set_input(87);
    write_op(0x1234, 0, input, PAGE_SIZE);
    read_op(0x1234, 0, output, PAGE_SIZE);

    volatile uint16_t val = validate(input, output, PAGE_SIZE);

    if (val == (uint16_t)-1)
        printf("read write success\n");
    else
        printf("read write failed at %d\n", val);

    /* Start */

    int i;
    for (i = 1; i <= 100; ++i)
    {
        printf("write page: %d.\n", i);

        set_input(i);
        write_op(i, 0, input, PAGE_SIZE);
        undo_log[undo_log_ptr++] = i;

        read_op(i, 0, output, PAGE_SIZE);
        volatile uint16_t val = validate(input, output, PAGE_SIZE);

        if (val == (uint16_t)-1)
            printf("read write success\n\n");
        else
            printf("read write failed at %d\n\n", val);

        if (i == 10)
        {
            printf("checkpoint at: %d\n\n", i);
            checkpoint();
        }
        else if (i == 20 && shutdown_test == 3)
        {
            shutdown_test--;
            vPortShutdown();
            printf("it shouldn't be printed.\n");
        }
        else if (i == 30)
        {
            printf("checkpoint at: %d\n\n", i);
            checkpoint();
        }
        else if (i == 50 && shutdown_test == 2)
        {
            shutdown_test--;
            vPortShutdown();
            printf("it shouldn't be printed.\n");
        }
        else if (i == 60)
        {
            printf("checkpoint at: %d\n\n", i);
            checkpoint();
        }
        else if (i == 90 && shutdown_test == 1)
        {
            shutdown_test--;
            vPortShutdown();
            printf("it shouldn't be printed.\n");
        }
    }
}
