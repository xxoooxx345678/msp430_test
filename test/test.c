#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard demo includes. */
#include "partest.h"

void test_main(void);

void test_main(void)
{
    while (1)
        vParTestToggleLED(0);

    for (;;);
}

