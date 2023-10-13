#include "FreeRTOS.h"

void DMA_transfer(uint8_t *src, uint8_t *dst, size_t size);

void vPortBackup();
void vPortRestore();
void vPortShutdown();
void checkpoint();
void restore();
