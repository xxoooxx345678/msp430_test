#include "FreeRTOS.h"

void vPortBackup();
void vPortRestore();
void vPortShutdown();
void checkpoint();
void checkpoint_nand();
void restore();
void restore_nand();
