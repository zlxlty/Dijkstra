/*
 * @Author: Tianyi Lu
 * @Description: 
 * @Date: 2021-10-04 22:32:23
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-10 18:57:18
 */

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HeapNode *_createNode(int index, int priority);
HeapNode *_parent(Miniheap *pHeap, int childPos);
HeapNode *heap_get_node(Miniheap *pHeap, int index);
void _swapNode(HeapNode *src, HeapNode *tar);
void _heapifyUp(Miniheap *pHeap, HeapNode *node);
void _heapifyDown(Miniheap *pHeap, HeapNode *node);

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

void heap_insert(Miniheap *pHeap, int index, int priority)
{
    if (pHeap == NULL || pHeap->nodes == NULL)
        return;

    int lastIndex = pHeap->length;

    HeapNode *newNode = _createNode(index, priority);

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

int *heap_extract_min(Miniheap *pHeap)
{
    if (pHeap->length <= 0)
        return NULL;

    HeapNode *lastNode = pHeap->nodes[pHeap->length - 1];

    HeapNode *minNode = pHeap->nodes[0];
    _swapNode(minNode, lastNode);

    pHeap->indexes[minNode->index] = minNode;

    int lastPos = pHeap->length - 1;
    pHeap->indexes[lastNode->index] = NULL;
    pHeap->nodes[lastPos] = NULL;
    HeapNode *parentNode = lastNode->parent;
    if (parentNode)
    {
        if (lastPos % 2 == 0)
        {
            parentNode->rightChild = NULL;
        }
        else
        {
            parentNode->leftChild = NULL;
        }
    }

    pHeap->length--;

    int *res = (int *)malloc(sizeof(int) * 2); //IMPORTANT! Remember to free res from outside!!!
    res[0] = lastNode->index;
    res[1] = lastNode->priority;
    free(lastNode);

    _heapifyDown(pHeap, minNode);

    return res;
}

HeapNode *heap_get_node(Miniheap *pHeap, int index)
{
    if (!pHeap || index >= pHeap->max || index < 0)
        return NULL;
    return pHeap->indexes[index];
}

void heap_change_priority(Miniheap *pHeap, int index, int newPriority)
{
    HeapNode* currNode = heap_get_node(pHeap, index);
    if (currNode) {
        int oldPriority = currNode->priority;
        currNode->priority = newPriority;
        if (newPriority > oldPriority)
        {
            _heapifyDown(pHeap, currNode);
        }
        else if (newPriority < oldPriority)
        {
            _heapifyUp(pHeap, currNode);
        }

    } else {
        printf("No node with index %d exists\n", index);
    }
}

void heap_free(Miniheap *pHeap)
{
    if (pHeap == NULL)
        return;

    for (int i = 0; i < pHeap->max; i++)
    {
        if (pHeap->nodes[i])
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
        printf("%d: (%d, %d) ", i, curr->index, curr->priority);
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
            printf("%d: (%d, %d) ", i, curr->index, curr->priority);
        }
    }
    printf("\n");
}

HeapNode *_createNode(int index, int priority)
{
    HeapNode *newNode = (HeapNode *)malloc(sizeof(HeapNode));
    newNode->priority = priority;
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
    int priority = src->priority;
    src->index = tar->index;
    src->priority = tar->priority;
    tar->index = index;
    tar->priority = priority;
}

void _heapifyUp(Miniheap *pHeap, HeapNode *node)
{
    if (node->parent == NULL)
        return;

    if (node->priority < node->parent->priority)
    {
        _swapNode(node, node->parent);
        pHeap->indexes[node->index] = node;
        pHeap->indexes[node->parent->index] = node->parent;

        _heapifyUp(pHeap, node->parent);
    }
}

void _heapifyDown(Miniheap *pHeap, HeapNode *node)
{
    if (pHeap->length <= 1 || (node->leftChild == NULL && node->rightChild == NULL))
        return;

    HeapNode *childNode = NULL;
    if (node->rightChild)
    {
        if (node->priority > node->rightChild->priority)
            childNode = node->rightChild;
    }

    if (node->priority > node->leftChild->priority)
        childNode = node->leftChild;

    if (childNode)
    {
        _swapNode(node, childNode);
        pHeap->indexes[node->index] = node;
        pHeap->indexes[childNode->index] = childNode;

        _heapifyDown(pHeap, childNode);
    }
}
