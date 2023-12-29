#include <msp430.h> 
#include "driverlib.h"
#include "NOR_RWE.h"
#include "my_timer.h"

/**
 * main.c
 */

#define BUFFER_SIZE 65536LL
#define BANK_SIZE (1LL << 15)

#pragma DATA_SECTION(buffer, ".test")
uint8_t buffer[BUFFER_SIZE];

//#pragma DATA_SECTION(bankc_buffer, ".bankc")
//uint8_t bankc_buffer[BANK_SIZE];
//
//#pragma DATA_SECTION(bankd_buffer, ".bankd")
//uint8_t bankd_buffer[BANK_SIZE];

int main(void)
{
    /* Stop WDT */
    WDT_A_hold(WDT_A_BASE);


    /* Set CPU frequency to 8MHz. */
    UCSCTL1 = DCORSEL_5;    // Select DCO range 16MHz operation
    UCSCTL2 |= 249;         // Set DCO Multiplier for 8MHz
                            // (N + 1) * FLLRef = Fdco
                            // (249 + 1) * 32768 = 8MHz


    __enable_interrupt();
    timer_init();
    timer_start();

    volatile uint32_t st, ed;
    volatile double elapsed_time;
    volatile double latency;
    volatile double throughput;

    uint16_t i;

    for (i = 0; i < 128; ++i)
        NOR_byte_write((uint8_t *)(buffer + i * 512));

    st = get_current_tick();
    __no_operation();

    FlashCtl_eraseSegment(buffer);

    __no_operation();

    ed = get_current_tick();
    elapsed_time = get_elasped_time(st, ed, 8000000);
    throughput = 512 / elapsed_time;
    latency = elapsed_time / 512;

	return 0;
}
