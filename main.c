#include <msp430.h>
#include "driverlib.h"
#include "spi_nand.h"
#include "my_timer.h"
#include "rng.h"

#define MEAN_1 500
#define STD_1	100
#define MIN_1	0
#define MAX_1	1000

#define MEAN_2 400
#define STD_2	100
#define MIN_2	-200
#define MAX_2	1000

#pragma NOINIT(input)
#pragma NOINIT(output)
uint8_t input[2048];
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

void nand_test()
{
	set_input();

	write_op(0x1694, 0, input, 2048);

	read_op(0x1694, 0, output, 2048);

	volatile uint16_t val = validate(input, output, 2048);

	if (val != (uint16_t)-1)
		__no_operation();

	erase_op(0x1692);

	read_op(0x1694, 0, output, 2048);

	clear_all_blocks();
}

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

	UCSCTL1 = DCORSEL_5; // Select DCO range 16MHz operation
	UCSCTL2 |= 249;		 // Set DCO Multiplier for 8MHz
					// (N + 1) * FLLRef = Fdco
					// (249 + 1) * 32768 = 8MHz

    __enable_interrupt();
    timer_init();
    timer_start();

	P2OUT &= ~BIT7;
	P2DIR |= BIT7;
	P2OUT |= BIT7;

	// USCB0 MOSI and MISO and Clock are P3.0, 3.1, and P3.2
	P3OUT &= ~(BIT0 + BIT1 + BIT2); // Set Initial Low
	P3DIR |= BIT0 + BIT2;			// Set MOSI and Clock as Output
	P3DIR &= ~BIT1;					// Set MISO as Input
	P3SEL |= BIT0 + BIT1 + BIT2;	// Give SPI control

	UCB0CTL1 |= UCSWRST; // **Put state machine in reset**
	UCB0CTL0 |= UCMST + UCSYNC + UCMSB + UCCKPH;
	UCB0CTL1 |= UCSSEL_2; // SMCLK
	UCB0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**

	if (spi_nand_init() != 0)
		return 1;

	uint8_t row;
	uint16_t col;
    volatile uint32_t st, ed, tt_tick = 0;
    volatile double elapsed_time;
    volatile double latency;
	for (row = 0; row < 20; ++row)
	{
		for (col = 0; col < PAGE_SIZE;)
		{
		    st = get_current_tick();
			*(int16_t *)(input + col) = norm_rand(MEAN_1, STD_1, MIN_1, MAX_1);
			*(int16_t *)(input + col + 2) = norm_rand(MEAN_2, STD_2, MIN_2, MAX_2);
			ed = get_current_tick();
			tt_tick += ed - st;
			col += 4;

		}
		//write_op(0x0116 + row, 0, input, PAGE_SIZE);
	}

	elapsed_time = get_elasped_time(0, tt_tick, 8000000);

	return 0;
}
