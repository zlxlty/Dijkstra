/*
 * @Author: Tianyi Lu
 * @Description: 
 * @Date: 2021-10-09 12:29:47
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-10 17:44:55
 */

#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct _heap_node
{
    struct _heap_node *parent;
    struct _heap_node *leftChild;
    struct _heap_node *rightChild;
    int index;
    int priority;
} HeapNode;

typedef struct _miniheap
{
    HeapNode **nodes;
    HeapNode **indexes;
    int length;
    int max;
} Miniheap;

#define MAX_HEAP_SIZE 1000

Miniheap *heap_init();
void heap_insert(Miniheap *pHeap, int index, int priority);
int *heap_extract_min(Miniheap *pHeap);
HeapNode *heap_get_node(Miniheap *pHeap, int index);
void heap_change_priority(Miniheap *pHeap, int index, int newPriority);
void heap_free(Miniheap *pHeap);
void heap_print(Miniheap *pHeap);
void heap_print_indexes(Miniheap *pHeap);

#endif