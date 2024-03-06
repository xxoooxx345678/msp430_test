#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "queue.h"
#include "checkpoint.h"
#include "my_timer.h"

#define tskTEST_PRIORITY (tskIDLE_PRIORITY + 1)
#define tskTEST_DELAY (pdMS_TO_TICKS(1000))

#pragma PERSISTENT(shutdown_cnt)
uint8_t shutdown_cnt = 4;

static void test(void *pvParameters);

void main_checkpoint(void)
{
    xTaskCreate(test, "test", configMINIMAL_STACK_SIZE, NULL, tskTEST_PRIORITY, NULL);
    vTaskStartScheduler();

    for (;;);
}

static void test(void *pvParameters)
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
