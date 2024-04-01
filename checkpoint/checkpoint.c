#include "driverlib.h"
#include "checkpoint.h"
#include <stdio.h>

#pragma PERSISTENT(snapshot)
Snapshot snapshot[SNAPSHOT_SLOT_COUNT] = {0};

void *snapshot_reg;

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

static Snapshot* find_next_open_snapshot_slot()
{
    Snapshot *ret = &snapshot;

    uint32_t min_timestamp = UINT32_MAX;
    uint8_t snapshot_idx;
    Snapshot *snapshot_ptr;

    for (snapshot_idx = 0; snapshot_idx < SNAPSHOT_SLOT_COUNT; ++snapshot_idx)
    {
        snapshot_ptr = &snapshot[snapshot_idx];
        if (snapshot_ptr->status != COMMIT_COMPLETE)
        {
            ret = snapshot_ptr;
            break;
        }
        else
        {
            if (snapshot_ptr->timestamp < min_timestamp)
            {
                min_timestamp = snapshot_ptr->timestamp;
                ret = snapshot_ptr;
            }
        }
    }

    return ret;
}

void checkpoint()
{
    Snapshot *open_snapshot = find_next_open_snapshot_slot();
    snapshot_reg = open_snapshot;
    open_snapshot->status = COMMIT_INCOMPLETE;
    extern uint32_t progress;
    open_snapshot->timestamp = progress;

    /*******************************************/
    /*              Program space              */
    /*******************************************/
    portENTER_CRITICAL();

    /* Backup SRAM and registers */
    DMA_transfer((uint8_t *)__bss__, (uint8_t *)open_snapshot->bss, BSS_SIZE);
    DMA_transfer((uint8_t *)__data__, (uint8_t *)open_snapshot->data, DATA_SIZE);
    DMA_transfer((uint8_t *)ucHeap, (uint8_t *)open_snapshot->heap, UCHEAP_SIZE);
    snapshotReg();

    portEXIT_CRITICAL();

    /*******************************************/
    /*              Storage space              */
    /*******************************************/
    portENTER_CRITICAL();

    // tree_checkpoint();

    portEXIT_CRITICAL();

    /* Commit completion flag */
    open_snapshot->status = COMMIT_COMPLETE;
}

static Snapshot* find_latest_complete_snapshot_slot()
{
    Snapshot *ret = NULL;

    uint32_t max_timestamp = 0;
    uint8_t snapshot_idx;
    Snapshot *snapshot_ptr;

    for (snapshot_idx = 0; snapshot_idx < SNAPSHOT_SLOT_COUNT; ++snapshot_idx)
    {
        snapshot_ptr = &snapshot[snapshot_idx];
        if (snapshot_ptr->status == COMMIT_COMPLETE && snapshot_ptr->timestamp > max_timestamp)
        {
            ret = snapshot_ptr;
            max_timestamp = snapshot_ptr->timestamp;
        }
    }

    return ret;
}

void restore()
{
    Snapshot *latest_snapshot = find_latest_complete_snapshot_slot();
    snapshot_reg = latest_snapshot;
    if (latest_snapshot == NULL)
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
    DMA_transfer((uint8_t *)latest_snapshot->bss, (uint8_t *)__bss__, BSS_SIZE);
    DMA_transfer((uint8_t *)latest_snapshot->data, (uint8_t *)__data__, DATA_SIZE);
    DMA_transfer((uint8_t *)latest_snapshot->heap, (uint8_t *)ucHeap, UCHEAP_SIZE);
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
