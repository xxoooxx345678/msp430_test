#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "spi_nand.h"
#include "benchmark.h"

void test_main(void);
static void nand_read_write_perf(void *pvParameters);
static void fram_read_write_perf(void *pvParameters);

void test_main(void)
{
//    xTaskCreate(nand_read_write_perf, "test", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
//
//    vTaskStartScheduler();

    fram_read_write_perf(NULL);
//    nand_read_write_perf(NULL);
}

static void fram_read_write_perf(void *pvParameters)
{
    volatile double read_latency = fram_latency_read(20480000);
   printf("read done, latency: %d nano seconds\n", (uint32_t)(read_latency*1000000000));
    volatile double write_latency = fram_latency_write(20480000);
    printf("write done, latency: %d nano seconds\n", (uint32_t)(write_latency*1000000000));
}

static void nand_read_write_perf(void *pvParameters)
{
    cs_drive_high();
#ifdef MT29F1G01ABAFDWB
    volatile int ret = spi_nand_init();

    if (ret != 0)
        return;

    nand_test();
    printf("test done\n");

    volatile double read_latency = nand_latency_read(1000);
    printf("read done, latency: %d micro seconds\n", (uint32_t)(read_latency*1000000));
    volatile double write_latency = nand_latency_write(1000);
    printf("write done, latency: %d micro seconds\n", (uint32_t)(write_latency*1000000));
//    volatile double erase_latency = latency_erase(10);
//    printf("erase done, latency: %d micro seconds\n", (uint32_t)(erase_latency*1000000));

#endif

#ifdef W25N01GVZEIG
    volatile int ret = spi_nand_init();

    if (ret != 0)
        return;

    test();
    printf("test done\n");

    volatile double read_latency = latency_read(100);
    printf("read done, latency: %d micro seconds\n", (uint16_t)(read_latency*1000000));
    volatile double write_latency = latency_write(100);
    printf("write done, latency: %d micro seconds\n", (uint16_t)(write_latency*1000000));
    volatile double erase_latency = latency_erase(100);
    printf("erase done, latency: %d micro seconds\n", (uint16_t)(erase_latency*1000000));

#endif
    for (;;);
}
