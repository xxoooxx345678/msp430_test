#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "FreeRTOS.h"

#define OP_BASED_EXPERIMENT 0
#define TIME_BASED_EXPERIMENT 1
#define EXPERIMENT TIME_BASED_EXPERIMENT

// In seconds
#if (EXPERIMENT == TIME_BASED_EXPERIMENT)
#define POWER_EVENT_INTERVAL 2 
#endif

#define SNAPSHOT_OPTIMIZATION

enum COMMIT_STATUS {
    COMMIT_INCOMPLETE = 0x87, 
    COMMIT_COMPLETE   = 0xAA
};

extern char __bss__[], __bssEnd__[], __data__[], __dataEnd__[];


#define BSS_SIZE (__bssEnd__ - __bss__)
#define DATA_SIZE (__dataEnd__ - __data__)
// #define STACK_SIZE                (__stackEnd__ - __stack__)
#ifdef SNAPSHOT_OPTIMIZATION
#define UCHEAP_SIZE 1000
#else
#define UCHEAP_SIZE (configTOTAL_HEAP_SIZE)
#endif

#define SNAPSHOT_SLOT_COUNT     4
#define SNAPSHOT_BSS_SIZE       1024
#define SNAPSHOT_DATA_SIZE      1024
// #define SNAPSHOT_STACK_SIZE     1024

typedef struct Snapshot {
    /* program context */
    uint32_t registers[16];
    uint8_t bss[SNAPSHOT_BSS_SIZE];
    uint8_t data[SNAPSHOT_DATA_SIZE];
    // uint8_t stack[STACK_SIZE];
    uint8_t heap[UCHEAP_SIZE];

    /* informations */
    uint32_t timestamp;
    uint8_t status;
} Snapshot;


void shutdown();
void checkpoint();
void restore();

#if (EXPERIMENT == TIME_BASED_EXPERIMENT)
void setup_power_event_timer();
#endif

#endif
