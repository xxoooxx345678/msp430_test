#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "queue.h"
#include "checkpoint.h"
#include <driverlib.h>
#include "my_timer.h"

#define tskTEST_PRIORITY (tskIDLE_PRIORITY + 1)
#define tskTEST_DELAY (pdMS_TO_TICKS(1000))

#pragma PERSISTENT(shutdown_cnt)
uint8_t shutdown_cnt = 4;

#if (EXPERIMENT == OP_BASED_EXPERIMENT)
static void test_op_based_power_event(void *pvParameters);
#endif

#if (EXPERIMENT == TIME_BASED_EXPERIMENT)
static void test_time_based_power_event(void *pvParameters);
#endif

void main_checkpoint(void)
{
#if (EXPERIMENT == OP_BASED_EXPERIMENT)
    xTaskCreate(test_op_based_power_event, "test", configMINIMAL_STACK_SIZE, NULL, tskTEST_PRIORITY, NULL);
#elif (EXPERIMENT == TIME_BASED_EXPERIMENT)
    xTaskCreate(test_time_based_power_event, "test", configMINIMAL_STACK_SIZE, NULL, tskTEST_PRIORITY, NULL);
#endif

    vTaskStartScheduler();

    for (;;);
}

#if (EXPERIMENT == OP_BASED_EXPERIMENT)
static void test_op_based_power_event(void *pvParameters)
{
    (void)pvParameters;

    uint16_t i;

    for (i = 1; i < 100; ++i)
    {
        if (i == 30)
            checkpoint();

        if (i == 20 && shutdown_cnt == 4)
        {
            --shutdown_cnt;
            shutdown();

            /* SHOULD NOT EXECUTE CODE BELOW */
            printf("YOU DARE USE MY OWN SPELL AGAINST ME POTTER!!!");
        }
        if (i == 40 && shutdown_cnt == 3)
        {
            --shutdown_cnt;
            shutdown();

            /* SHOULD NOT EXECUTE CODE BELOW */
            printf("YOU SHALL NOT PASS!!!");
        }
        if (i == 50 && shutdown_cnt == 2)
        {
            --shutdown_cnt;
            shutdown();

            /* SHOULD NOT EXECUTE CODE BELOW */
            printf("I DON'T LIKE SAND.");
        }
        if (i == 99 && shutdown_cnt == 1)
        {
            --shutdown_cnt;
            shutdown();

            /* SHOULD NOT EXECUTE CODE BELOW */
            printf("WE NEED TO GO DEEPER.");
        }

        printf("%d\n", i);
    }

    for (;;);
}
#endif

#if (EXPERIMENT == TIME_BASED_EXPERIMENT)
/* Add "progress" to expression and set breakpoint at A3_ISR & restore to check their functionalities */
uint32_t progress = 1;
static void test_time_based_power_event(void *pvParameters)
{
    while (1)
    {
        if (progress % 1000 == 0)
        {
            checkpoint();
            printf("CHECKPOINT AT i = %u\n", progress);
        }

        ++progress;
        __delay_cycles(1000);
        /* printing "progress" here is strongly not recommended */
    }

    for (;;);
}
#endif
