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

#pragma PERSISTENT(rtc_alarm_param)
RTC_C_configureCalendarAlarmParam rtc_alarm_param = {.minutesAlarm = 0x1};

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
    RTC_C_initCalendar(RTC_C_BASE, &rtc_calendar_param, RTC_C_FORMAT_BCD);
    RTC_C_configureCalendarAlarm(RTC_C_BASE, &rtc_alarm_param);

    PMM_turnOffRegulator();
    PMM_disableSVSH();

    RTC_C_enableInterrupt(RTC_C_BASE, RTC_C_CLOCK_ALARM_INTERRUPT);
    RTC_C_startClock(RTC_C_BASE);
    LPM4;
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
    RTC_C_clearInterrupt(RTC_C_BASE, RTC_C_CLOCK_ALARM_INTERRUPT);
    __no_operation();
}

// For time based power event experiment
#if (EXPERIMENT == TIME_BASED_EXPERIMENT)
void setup_power_event_timer()
{

}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void A1_ISR( void )
{
    TA1CTL &= ~TAIFG;

    __bic_SR_register_on_exit( SCG1 + SCG0 + OSCOFF + CPUOFF );
}

#endif
