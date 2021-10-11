/*
 * @Author: Tianyi Lu
 * @Description: 
 * @Date: 2021-10-09 17:27:44
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-10 19:08:35
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Heap/heap.h"
#include "Graph/graph.h"

extern Miniheap *heap_init();
extern void heap_insert(Miniheap *pHeap, int index, int priority);
extern int *heap_extract_min(Miniheap *pHeap);
extern HeapNode *heap_get_node(Miniheap *pHeap, int index);
extern void heap_change_priority(Miniheap *pHeap, int index, int newPriority);
extern void heap_free(Miniheap *pHeap);
extern void heap_print(Miniheap *pHeap);
extern void heap_print_indexes(Miniheap *pHeap);

extern Graph *graph_init(int numNodes, int initNum);
extern void graph_add_edge(Graph *pGraph, int startVertexIndex,
                    int endVertexIndex, int value);
extern void graph_free(Graph *pGraph);

int *dijkstra(Graph *pGraph, int start)
{
    if (!pGraph)
    {
        exit(1);
    }

    Miniheap *pHeap = heap_init();
    for (int i = 0; i < pGraph->numNodes; i++)
    {
        int priority = INT_MAX;
        if (i == start)
            priority = 0;

        heap_insert(pHeap, i, priority);
    }

    int *shortest = (int *)malloc(sizeof(int) * pGraph->numNodes);
    memset(shortest, -1, sizeof(int) * pGraph->numNodes);
    while (pHeap->length > 0)
    {
        int *result = heap_extract_min(pHeap);
        int vertex = result[0];
        int distance = result[1];
        shortest[vertex] = distance;

        for (int i = 0; i < pGraph->numNodes; i++) {
            int edgeWeight = pGraph->edges[vertex][i];
            if (edgeWeight) {
                HeapNode* neighbor = heap_get_node(pHeap, i);
                if (neighbor) {
                    int distanceTo = distance + edgeWeight;
                    if (distanceTo < neighbor->priority)
                        heap_change_priority(pHeap, i, distanceTo);
                }
            }
        }

        free(result);
    }

    heap_free(pHeap);
    return shortest;
}

int main(int argc, char const *argv[])
{
    Graph *pGraph = graph_init(6, 0);
    graph_add_edge(pGraph, 0, 1, 7);
    graph_add_edge(pGraph, 0, 2, 12);
    graph_add_edge(pGraph, 1, 2, 2);
    graph_add_edge(pGraph, 1, 3, 9);
    graph_add_edge(pGraph, 2, 4, 10);
    graph_add_edge(pGraph, 3, 5, 1);
    graph_add_edge(pGraph, 4, 3, 4);
    graph_add_edge(pGraph, 4, 5, 5);

    int *shortestDistance = dijkstra(pGraph, 0);
    for (int i = 0; i < pGraph->numNodes; i++)
        printf("\nshortest distance to %d is : %d\n\n", i, shortestDistance[i]);

    free(shortestDistance);
    graph_free(pGraph);
    return 0;
}