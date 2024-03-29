#include "driverlib.h"
#include "checkpoint.h"
#include <stdio.h>

#pragma PERSISTENT(snapshot)
Snapshot snapshot = {0};

#pragma PERSISTENT(dma_param)
DMA_initParam dma_param = {0};

#pragma PERSISTENT(rtc_calendar_param)
Calendar rtc_calendar_param = {.Seconds = 0x59,
                               .Minutes = 0x0,
                               .Hours = 0x0,
                               .DayOfWeek = 0x0,
                               .DayOfMonth = 0x0,
                               .Month = 0x0,
                               .Year = 0x0
                               };

extern uint8_t ucHeap[configTOTAL_HEAP_SIZE];

extern void snapshotReg();
extern void restoreReg();

static void DMA_transfer(uint8_t *src, uint8_t *dst, size_t size)
{
    DMA_setTransferSize(dma_param.channelSelect, (size + 1) / 2); // Byte -> Word
    DMA_setSrcAddress(dma_param.channelSelect, (uint32_t)src, DMA_DIRECTION_INCREMENT);
    DMA_setDstAddress(dma_param.channelSelect, (uint32_t)dst, DMA_DIRECTION_INCREMENT);
    DMA_enableTransfers(dma_param.channelSelect);

    DMA_startTransfer(dma_param.channelSelect);
}

void shutdown()
{
    portENTER_CRITICAL();

    RTC_C_disableInterrupt(RTC_C_BASE, RTC_C_TIME_EVENT_INTERRUPT + RTC_C_CLOCK_ALARM_INTERRUPT + RTC_C_CLOCK_READ_READY_INTERRUPT + RTC_C_OSCILLATOR_FAULT_INTERRUPT);
    RTC_C_clearInterrupt(RTC_C_BASE, RTC_C_TIME_EVENT_INTERRUPT + RTC_C_CLOCK_ALARM_INTERRUPT + RTC_C_CLOCK_READ_READY_INTERRUPT + RTC_C_OSCILLATOR_FAULT_INTERRUPT);
    RTC_C_initCalendar(RTC_C_BASE, &rtc_calendar_param, RTC_C_FORMAT_BCD);
    RTC_C_setCalendarEvent(RTC_C_BASE, RTC_C_CALENDAREVENT_MINUTECHANGE);
    RTC_C_enableInterrupt(RTC_C_BASE, RTC_C_TIME_EVENT_INTERRUPT);

    PMM_turnOffRegulator();
    PMM_disableSVSH();

    RTC_C_startClock(RTC_C_BASE);
    LPM4;

    portEXIT_CRITICAL();
}

void checkpoint()
{
    /*******************************************/
    /*              Program space              */
    /*******************************************/
    portENTER_CRITICAL();

    /* Backup SRAM and registers */
    DMA_transfer((uint8_t *)__bss__, (uint8_t *)snapshot.bss, BSS_SIZE);
    DMA_transfer((uint8_t *)__data__, (uint8_t *)snapshot.data, DATA_SIZE);
    DMA_transfer((uint8_t *)ucHeap, (uint8_t *)snapshot.heap, configTOTAL_HEAP_SIZE);
    snapshotReg();

    portEXIT_CRITICAL();

    /*******************************************/
    /*              Storage space              */
    /*******************************************/
    portENTER_CRITICAL();

    // tree_checkpoint();

    portEXIT_CRITICAL();

    /* Commit completion flag */
    snapshot.commit_flag = COMMIT_COMPLETE;
}

void restore()
{
    if (snapshot.commit_flag != COMMIT_COMPLETE)
        return;

    /*******************************************/
    /*              Storage space              */
    /*******************************************/
    portENTER_CRITICAL();

    // tree_restore();

    portEXIT_CRITICAL();

    /*******************************************/
    /*              Program space              */
    /*******************************************/
    portENTER_CRITICAL();

    /* Restore SRAM and registers */
    DMA_transfer((uint8_t *)snapshot.bss, (uint8_t *)__bss__, BSS_SIZE);
    DMA_transfer((uint8_t *)snapshot.data, (uint8_t *)__data__, DATA_SIZE);
    DMA_transfer((uint8_t *)snapshot.heap, (uint8_t *)ucHeap, configTOTAL_HEAP_SIZE);
    restoreReg();

    /* Never reach here */
    portEXIT_CRITICAL();
}

#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR( void )
{
    RTC_C_clearInterrupt(RTC_C_BASE, RTC_C_TIME_EVENT_INTERRUPT + RTC_C_CLOCK_ALARM_INTERRUPT + RTC_C_CLOCK_READ_READY_INTERRUPT + RTC_C_OSCILLATOR_FAULT_INTERRUPT);
}

// For time based power event experiment
#if (EXPERIMENT == TIME_BASED_EXPERIMENT)
void setup_power_event_timer()
{
    Timer_A_initUpModeParam initUpParam = {0};
    initUpParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;

    /* To configure the power event interval, compute and set these two values down below */
    initUpParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_2;
    initUpParam.timerPeriod = (0xFFFF >> 1);

    initUpParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;
    initUpParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    initUpParam.timerClear = TIMER_A_DO_CLEAR;
    initUpParam.startTimer = false;
    Timer_A_initUpMode(TIMER_A3_BASE, &initUpParam);

    Timer_A_clear(TIMER_A3_BASE);
    Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_UP_MODE);
}

#pragma vector=TIMER3_A1_VECTOR
__interrupt void A3_ISR( void )
{
    TA3CTL &= ~TAIFG;

    shutdown();

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
}

#endif
