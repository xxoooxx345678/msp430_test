#include "my_timer.h"
#include "FreeRTOS.h"
#include "driverlib.h"

#pragma PERSISTENT(elapsed_tick)
uint32_t elapsed_tick = 0;

void timer_init()
{
    Timer_A_initContinuousModeParam initContParam = {0};
    initContParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    initContParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1; 
    initContParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
    initContParam.timerClear = TIMER_A_DO_CLEAR;
    initContParam.startTimer = false;
    Timer_A_initContinuousMode(TIMER_A1_BASE, &initContParam);

    Timer_A_enableInterrupt(TIMER_A1_BASE);
}

double get_elasped_time(uint32_t start, uint32_t end, uint32_t TIMER_FREQ)
{
    return ((double)(end - start) / TIMER_FREQ);
}

void timer_start()
{
    Timer_A_clear(TIMER_A1_BASE);
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_CONTINUOUS_MODE);
}

uint32_t get_current_tick()
{
    uint16_t tmp_time = Timer_A_getCounterValue(TIMER_A1_BASE);
    return (uint32_t)tmp_time + elapsed_tick;
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void v4RunTimeStatsTimerOverflow( void )
{
	TA1CTL &= ~TAIFG;
	
	/* 16-bit overflow, so add 17th bit. */
	elapsed_tick += 0x10000;
	__bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
}