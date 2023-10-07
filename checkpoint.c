#include "FreeRTOS.h"
#include "checkpoint.h"
#include <stdio.h>
#include <string.h>
#include "spi_nand.h"

extern uint8_t backuped;

#pragma NOINIT(reg_buffer)
#pragma NOINIT(pc_buffer)
#pragma NOINIT(sp_buffer)
#pragma NOINIT(ret_buffer)
uint32_t reg_buffer[14];
uint32_t pc_buffer;
uint32_t sp_buffer;
uint32_t ret_buffer;

#pragma PERSISTENT(backup_buffer)
uint8_t backup_buffer[1024 * 8] = {0};
#pragma PERSISTENT(heap_buffer)
uint8_t heap_buffer[configTOTAL_HEAP_SIZE] = {0};
extern uint8_t ucHeap[configTOTAL_HEAP_SIZE];

extern uint32_t undo_log[128];
extern uint8_t undo_log_ptr;

void vPortBackup()
{
    backuped = 1;

//    __data20_write_long((uintptr_t)&DMA0SA, (uintptr_t)ucHeap);      // Source block address
//    __data20_write_long((uintptr_t)&DMA0DA, (uintptr_t)heap_buffer); // Destination single address
//    DMA0SZ = configTOTAL_HEAP_SIZE / 2;                              // Block size
//    DMA0CTL = DMADT_1 | DMASRCINCR_3 | DMADSTINCR_3;                 // | DMADSTBYTE_1 | DMASRCBYTE_1; // Rpt, inc
//    DMA0CTL |= DMAEN;                                                // Enable DMA0
//    DMA0CTL |= DMAREQ;                                               // Trigger block transfer



    extern void vPortBackupASM(void);
    vPortBackupASM();
    
    uint32_t i;
    for (i = 0; i < configTOTAL_HEAP_SIZE; ++i)
        heap_buffer[i] = ucHeap[i];
}

void vPortRestore()
{
//    __data20_write_long((uintptr_t)&DMA0SA, (uintptr_t)heap_buffer); // Source block address
//    __data20_write_long((uintptr_t)&DMA0DA, (uintptr_t)ucHeap);      // Destination single address
//    DMA0SZ = configTOTAL_HEAP_SIZE / 2;                              // Block size
//    DMA0CTL = DMADT_1 | DMASRCINCR_3 | DMADSTINCR_3;                 // | DMADSTBYTE_1 | DMASRCBYTE_1; // Rpt, inc
//    DMA0CTL |= DMAEN;                                                // Enable DMA0
//    DMA0CTL |= DMAREQ;                                               // Trigger block transfer

    uint32_t i;
    for (i = 0; i < configTOTAL_HEAP_SIZE; ++i)
        ucHeap[i] = heap_buffer[i];

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
    portENTER_CRITICAL();
    vPortBackup();
    portEXIT_CRITICAL();
}

void checkpoint_nand()
{
    // int i;
    // for (i = 0; i < undo_log_ptr; ++i)
    //     undo_log[i] = 0;
    undo_log_ptr = 0;
}

void restore()
{
    portENTER_CRITICAL();
    vPortRestore();
    portEXIT_CRITICAL();
}

void restore_nand()
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
