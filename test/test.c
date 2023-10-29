#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "spi_nand.h"
#include "benchmark.h"

void test_main(void);
static void nand_read_write_perf(void *pvParameters);


void test_main(void)
{
    xTaskCreate(nand_read_write_perf, "test", 512, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();
}

static void nand_read_write_perf(void *pvParameters)
{
    cs_drive_high();
#ifdef MT29F1G01ABAFDWB
    volatile int ret = spi_nand_init();

    if (ret != 0)
        return;

    test();
    printf("test done\n");

    volatile double read_latency = latency_read(100);
    printf("read done, latency: %d micro seconds\n", (uint32_t)(read_latency*1000000));
    volatile double write_latency = latency_write(100);
    printf("write done, latency: %d micro seconds\n", (uint32_t)(write_latency*1000000));
    volatile double erase_latency = latency_erase(10);
    printf("erase done, latency: %d micro seconds\n", (uint32_t)(erase_latency*1000000));

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
