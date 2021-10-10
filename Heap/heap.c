/*
 * @Author: Tianyi Lu
 * @Description: 
 * @Date: 2021-10-04 22:32:23
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-10 08:58:55
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HeapNode *_createNode(int index, int distance);
HeapNode *_parent(Miniheap *pHeap, int childPos);
void _swapNode(HeapNode *src, HeapNode *tar);
void _heapifyUp(Miniheap *pHeap, HeapNode *node);

Miniheap *heap_init()
{
    Miniheap *pHeap = (Miniheap *)malloc(sizeof(Miniheap));
    pHeap->length = 0;
    pHeap->max = MAX_HEAP_SIZE;
    pHeap->nodes = (HeapNode **)malloc(sizeof(HeapNode *) * pHeap->max);
    pHeap->indexes = (HeapNode **)malloc(sizeof(HeapNode *) * pHeap->max);

    for (int i = 0; i < pHeap->max; i++)
    {
        pHeap->nodes[i] = NULL;
        pHeap->indexes[i] = NULL;
    }

    return pHeap;
}

void heap_insert(Miniheap *pHeap, int index, int distance)
{
    if (pHeap == NULL || pHeap->nodes == NULL)
        return;

    int lastIndex = pHeap->length;

    HeapNode *newNode = _createNode(index, distance);

    pHeap->nodes[lastIndex] = newNode;
    HeapNode *parentNode = _parent(pHeap, lastIndex);
    newNode->parent = parentNode;
    if (parentNode)
    {
        if (!parentNode->leftChild)
        {
            parentNode->leftChild = newNode;
        }
        else
        {
            parentNode->rightChild = newNode;
        }
    }

    pHeap->indexes[index] = newNode;
    _heapifyUp(pHeap, newNode);

    pHeap->length++;
}

HeapNode *heap_get_node(Miniheap *pHeap, int index)
{
    return pHeap->indexes[index];
}

void heap_free(Miniheap *pHeap)
{
    if (pHeap == NULL)
        return;

    for (int i = 0; i < pHeap->max; i++)
    {
        free(pHeap->nodes[i]);
    }
    free(pHeap->nodes);
    free(pHeap->indexes);
    free(pHeap);
}

void heap_print(Miniheap *pHeap)
{
    if (pHeap == NULL)
        return;

    for (int i = 0; i < pHeap->length; i++)
    {
        HeapNode *curr = pHeap->nodes[i];
        printf("%d: (%d, %d) ", i, curr->index, curr->distance);
    }
    printf("\n");
}

void heap_print_indexes(Miniheap *pHeap)
{
    if (pHeap == NULL)
        return;

    for (int i = 0; i < pHeap->max; i++)
    {
        HeapNode *curr = pHeap->indexes[i];
        if (curr != NULL)
        {
            printf("%d: (%d, %d) ", i, curr->index, curr->distance);
        }
    }
    printf("\n");
}

HeapNode *_createNode(int index, int distance)
{
    HeapNode *newNode = (HeapNode *)malloc(sizeof(HeapNode));
    newNode->distance = distance;
    newNode->index = index;
    newNode->parent = newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
}

HeapNode *_parent(Miniheap *pHeap, int childPos)
{
    if (childPos <= 0 || childPos >= pHeap->max)
    {
        return NULL;
    }
    else
    {
        int parentPos = (childPos - 1) / 2;
        return pHeap->nodes[parentPos];
    }
}

void _swapNode(HeapNode *src, HeapNode *tar)
{
    int index = src->index;
    int distance = src->distance;
    src->index = tar->index;
    src->distance = tar->distance;
    tar->index = index;
    tar->distance = distance;
}

void _heapifyUp(Miniheap *pHeap, HeapNode *node)
{
    if (node->parent == NULL)
        return;

    if (node->distance < node->parent->distance)
    {
        _swapNode(node, node->parent);
        pHeap->indexes[node->index] = node;
        pHeap->indexes[node->parent->index] = node->parent;

        _heapifyUp(pHeap, node->parent);
    }
}
