#include "checkpoint.h"
#include "driverlib.h"
#include <stdio.h>

#pragma PERSISTENT(snapshot)
Snapshot snapshot = {0};

#pragma PERSISTENT(dma_param)
DMA_initParam dma_param = {0};

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
    PMM_turnOffRegulator();
    PMM_disableSVSH();
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
    DMA_transfer((uint8_t *)snapshot.data,(uint8_t *)__data__,  DATA_SIZE);
    DMA_transfer((uint8_t *)snapshot.heap,(uint8_t *)ucHeap,  configTOTAL_HEAP_SIZE);
    restoreReg();

    /* Never reach here */
    portEXIT_CRITICAL();
}
