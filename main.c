#include <msp430.h> 
#include <stdlib.h>
#include <time.h>
#include <driverlib.h>
#include "my_timer.h"

#define TREE_SIZE 50

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

uint16_t treeShape[256] = {0};
uint16_t treeShape_id = 0;

#pragma DATA_SECTION(tree, ".tree");
uint8_t tree[512];

ArrNode *const arrTree = (ArrNode *)tree;
PtrNode *const ptrTree = (PtrNode *)tree;

uint16_t node_id = 0;

void shapeTree(uint16_t size)
{
    if (size == 0)
        return;

    uint16_t lt_size = size > 1 ? rand() % (size - 1) : 0;
    uint16_t rt_size = size - 1 - lt_size;

    treeShape[treeShape_id++] = lt_size;
    treeShape[treeShape_id++] = rt_size;

    shapeTree(lt_size);
    shapeTree(rt_size);
}

uint16_t initArrayTree(uint16_t size)
{
    if (size == 0)
        return (uint16_t)-1;

    uint16_t lt_size = treeShape[treeShape_id++];
    uint16_t rt_size = treeShape[treeShape_id++];

    uint16_t tmp_node_offset = node_id++;

    uint16_t left_child_offset = initArrayTree(lt_size);
    uint16_t right_child_offset = initArrayTree(rt_size);

    ArrNode tmp = {
        .child = {left_child_offset, right_child_offset},
        .record = {tmp_node_offset, tmp_node_offset}
    };

    FlashCtl_write8((uint8_t *)&tmp, (uint8_t *)&arrTree[tmp_node_offset], sizeof(ArrNode));

    return tmp_node_offset;
}

PtrNode *initPtrTree(uint16_t size)
{
    if (size == 0)
        return NULL;

    uint16_t lt_size = treeShape[treeShape_id++];
    uint16_t rt_size = treeShape[treeShape_id++];

    uint16_t tmp_node_offset = node_id++;

    PtrNode *left_child_ptr = initPtrTree(lt_size);
    PtrNode *right_child_ptr = initPtrTree(rt_size);

    PtrNode tmp = {
        .child = {left_child_ptr, right_child_ptr},
        .record = {tmp_node_offset, tmp_node_offset}
    };

    FlashCtl_write8((uint8_t *)&tmp, (uint8_t *)&ptrTree[tmp_node_offset], sizeof(PtrNode));

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
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    UCS_initFLL(16000, 250); // Set SMCLK to 8MHz

    timer_init(); // Init timer
    timer_start();
    uint32_t st, ed;

    shapeTree(TREE_SIZE);

    /*-----------Array Tree-------------*/

    // Init arrTree
    FlashCtl_eraseSegment(tree);
    node_id = 0;
    treeShape_id = 0;
    initArrayTree(TREE_SIZE);

    // Get elapsed time of array tree traversal
    st = get_current_tick();
    arrTreeDFS(arrTree);
    ed = get_current_tick();

    volatile double array_elapsed_time = get_elasped_time(st, ed, UCS_getSMCLK());

    /*----------Pointer Tree------------*/

    // Init ptrTree
    FlashCtl_eraseSegment(tree);
    node_id = 0;
    treeShape_id = 0;
    initPtrTree(TREE_SIZE);

    // Get elapsed time of pointer tree traversal
    st = get_current_tick();
    PtrTreeDFS(ptrTree);
    ed = get_current_tick();

    volatile double ptr_elapsed_time = get_elasped_time(st, ed, UCS_getSMCLK());

    return 0;
}
