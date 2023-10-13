#include "FreeRTOS.h"
#include "checkpoint.h"
#include <stdio.h>
#include <string.h>
#include "spi_nand.h"
#include "driverlib.h"
#include "my_timer.h"
#include "config.h"

extern uint8_t backuped;

#pragma NOINIT(reg_buffer)
#pragma NOINIT(pc_buffer)
#pragma NOINIT(sp_buffer)
#pragma NOINIT(ret_buffer)
uint32_t reg_buffer[14];
uint32_t pc_buffer;
uint32_t sp_buffer;
uint32_t ret_buffer;


#pragma PERSISTENT(heap_buffer)
uint8_t heap_buffer[configTOTAL_HEAP_SIZE] = {0};
extern uint8_t ucHeap[configTOTAL_HEAP_SIZE];

extern uint32_t undo_log[128];
extern uint8_t undo_log_ptr;

#pragma PERSISTENT(dma_param)
DMA_initParam dma_param = {0};

void DMA_transfer(uint8_t *src, uint8_t *dst, size_t size)
{
    dma_param.channelSelect = DMA_CHANNEL_0;
    dma_param.transferModeSelect = DMA_TRANSFER_BLOCK;
    dma_param.transferUnitSelect = DMA_SIZE_SRCWORD_DSTWORD;
    DMA_init(&dma_param);

    DMA_setTransferSize(dma_param.channelSelect, size / 2); // Byte -> Word
    DMA_setSrcAddress(dma_param.channelSelect, (uint32_t)src, DMA_DIRECTION_INCREMENT);
    DMA_setDstAddress(dma_param.channelSelect, (uint32_t)dst, DMA_DIRECTION_INCREMENT);
    DMA_enableTransfers(dma_param.channelSelect);

    DMA_startTransfer(dma_param.channelSelect);
}

void vPortBackup()
{
    backuped = 1;

    volatile uint32_t st, ed;


    extern void vPortBackupASM(void);
    vPortBackupASM();
    st = get_current_tick();

#ifdef UCHEAP_SHRINK
    DMA_transfer(ucHeap, heap_buffer, UCHEAP_SHRINKED_BACKUP_SIZE);
#else
    DMA_transfer(ucHeap, heap_buffer, configTOTAL_HEAP_SIZE);
#endif

    ed = get_current_tick();
    volatile double elapsed_time = ((double)(ed - st)) / 8000000;

    return;
}

void vPortRestore()
{
#ifdef UCHEAP_SHRINK
    DMA_transfer(heap_buffer, ucHeap, UCHEAP_SHRINKED_BACKUP_SIZE);
#else
    DMA_transfer(heap_buffer, ucHeap, configTOTAL_HEAP_SIZE);
#endif

    extern void vPortRestoreASM(void);
    vPortRestoreASM();
}

void vPortShutdown()
{
    extern void vPortShutdownASM();
    vPortShutdownASM();
}

void checkpoint()
{
#ifdef WITH_NAND_FLASH
    checkpoint_nand();
#endif

    portENTER_CRITICAL();
    vPortBackup();
    portEXIT_CRITICAL();
}

static void checkpoint_nand()
{
    // int i;
    // for (i = 0; i < undo_log_ptr; ++i)
    //     undo_log[i] = 0;
    undo_log_ptr = 0;
}

void restore()
{
#ifdef WITH_NAND_FLASH
    restore_nand();
#endif

    portENTER_CRITICAL();
    vPortRestore();
    portEXIT_CRITICAL();
}

static void restore_nand()
{
    int i;
    uint32_t j;
    uint32_t backup_block = 0x0116;
    uint8_t tmp_page[PAGE_SIZE];

    for (i = 0; i < undo_log_ptr; ++i)
    {
        uint32_t block_addr = undo_log[i] & 0xFFE0;

        erase_op(backup_block);
        for (j = 0; j < PAGES_PER_BLOCK && j < (undo_log[i] & 0x001F); ++j)
        {
            read_op(block_addr + j, 0, tmp_page, PAGE_SIZE);
            write_op(backup_block + j, 0, tmp_page, PAGE_SIZE);
        }

        erase_op(block_addr);
        for (j = 0; j < PAGES_PER_BLOCK && j < (undo_log[i] & 0x001F); ++j)
        {
            read_op(backup_block + j, 0, tmp_page, PAGE_SIZE);
            write_op(block_addr + j, 0, tmp_page, PAGE_SIZE);
        }
    }

    // for (i = 0; i < undo_log_ptr; ++i)
        // undo_log[i] = 0;
    undo_log_ptr = 0;
}
