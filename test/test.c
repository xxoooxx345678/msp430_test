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

//    if (ret != 0)
//        return;

    test();
    printf("test done\n");

    energy_consumption_read_write(1000);

#endif

#ifdef W25N01GVZEIG
    volatile int ret = spi_nand_init();

    if (ret != 0)
        return;

    test();
    printf("test done\n");

    energy_consumption_read_write(1000);
#endif
    for (;;);
}
