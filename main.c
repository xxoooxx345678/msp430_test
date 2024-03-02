#include <msp430.h> 
#include <driverlib.h>
#include <stdlib.h>
#include <time.h>
#include "my_timer.h"

void setupHW()
{
    WDT_A_hold( __MSP430_BASEADDRESS_WDT_A__ );

    MPU_initTwoSegments(MPU_BASE, 0x400, MPU_READ | MPU_WRITE | MPU_EXEC, MPU_READ | MPU_WRITE | MPU_EXEC);

	/* Set DCO frequency to 8 MHz. */
	CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_6);

	/* Set external clock frequency to 32.768 KHz. */
	CS_setExternalClockSource(32768, 0);

	/* Set SMCLK = DCO with frequency divider of 1. */
	CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

	/* Set MCLK = DCO with frequency divider of 1. */
	CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

	/* Disable the GPIO power-on default high-impedance mode. */
	PMM_unlockLPM5();
}

typedef struct Record {
    uint8_t x;
    uint8_t y;
} Record;

typedef struct ArrNode {
    uint16_t child[2]; // child array
    Record record;
} ArrNode;

typedef struct PtrNode {
    struct PtrNode *child[2];
    Record record;
} PtrNode;

#pragma DATA_SECTION(tree, ".tree")
uint8_t tree[1024]; 

ArrNode * const arrTree = (ArrNode *)tree;
PtrNode * const ptrTree = (PtrNode *)tree;

uint16_t node_id = 0;

uint16_t initArrayTree(uint16_t size)
{
    if (size == 0)
        return (uint16_t)-1;

    uint16_t lt_size = size > 1 ? rand() % (size - 1) : 0;
    uint16_t rt_size = size - 1 - lt_size;
    
    uint16_t tmp_node_offset = node_id++;

    uint16_t left_child_offset = initArrayTree(lt_size);
    uint16_t right_child_offset = initArrayTree(rt_size);

    ArrNode tmp = {
        .child = {left_child_offset, right_child_offset},
        .record = {tmp_node_offset, tmp_node_offset}
    };

	arrTree[tmp_node_offset] = tmp;

    return tmp_node_offset;
}

PtrNode *initPtrTree(uint16_t size)
{
    if (size == 0)
        return NULL;

    uint16_t lt_size = size > 1 ? rand() % (size - 1) : 0;
    uint16_t rt_size = size - 1 - lt_size;
    
    uint16_t tmp_node_offset = node_id++;

    PtrNode *left_child_ptr = initPtrTree(lt_size);
    PtrNode *right_child_ptr = initPtrTree(rt_size);

    PtrNode tmp = {
        .child = {left_child_ptr, right_child_ptr},
        .record = {tmp_node_offset, tmp_node_offset}
    };

	ptrTree[tmp_node_offset] = tmp;

    return &ptrTree[tmp_node_offset];
}

void arrTreeDFS(ArrNode *node)
{
    if (node->child[0] != (uint16_t)-1)
        arrTreeDFS(&arrTree[node->child[0]]);
    if (node->child[1] != (uint16_t)-1)
        arrTreeDFS(&arrTree[node->child[1]]);
}

void PtrTreeDFS(PtrNode *node)
{
    if (node->child[0] != NULL)
        PtrTreeDFS(node->child[0]);
    if (node->child[1] != NULL)
        PtrTreeDFS(node->child[1]);
}

/**
 * main.c
 */
int main(void)
{
	setupHW();

    timer_init(); // Init timer
    timer_start();
    uint32_t st, ed;

    /*-----------Array Tree-------------*/

    // Init arrTree
    node_id = 0;
    initArrayTree(50);

    // Get elapsed time of array tree traversal
    st = get_current_tick();
    arrTreeDFS(arrTree);
    ed = get_current_tick();

    volatile double array_elapsed_time = get_elasped_time(st, ed, CS_getSMCLK());

    /*----------Pointer Tree------------*/

    // Init ptrTree
    node_id = 0;
    initPtrTree(50);

    // Get elapsed time of pointer tree traversal
    st = get_current_tick();
    PtrTreeDFS(ptrTree);
    ed = get_current_tick();

    volatile double ptr_elapsed_time = get_elasped_time(st, ed, CS_getSMCLK());

	return 0;
}
