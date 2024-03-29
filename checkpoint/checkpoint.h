#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "FreeRTOS.h"

#define OP_BASED_EXPERIMENT 0
#define TIME_BASED_EXPERIMENT 1
#define EXPERIMENT TIME_BASED_EXPERIMENT

enum COMMIT_STATUS {
    COMMIT_INCOMPLETE = 0x87, // Do we even need this ?
    COMMIT_COMPLETE   = 0xAA
};

extern char __bss__[], __bssEnd__[], __data__[], __dataEnd__[];

#define BSS_SIZE                (__bssEnd__ - __bss__)          
#define DATA_SIZE                (__dataEnd__ - __data__)          
// #define STACK_SIZE                (__stackEnd__ - __stack__)          

#define SNAPSHOT_SLOT_COUNT     2
#define SNAPSHOT_BSS_SIZE       1024
#define SNAPSHOT_DATA_SIZE      1024
// #define SNAPSHOT_STACK_SIZE     1024

typedef struct Snapshot {
    uint32_t registers[16];
    uint8_t bss[SNAPSHOT_BSS_SIZE];
    uint8_t data[SNAPSHOT_DATA_SIZE];
    // uint8_t stack[STACK_SIZE];

    uint8_t heap[configTOTAL_HEAP_SIZE];
    uint8_t commit_flag;
} Snapshot;

void shutdown();
void checkpoint();
void restore();

#if (EXPERIMENT == TIME_BASED_EXPERIMENT)
void setup_power_event_timer();
#endif

#endif
