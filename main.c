/*
 * @Author: Tianyi Lu
 * @Description: 
 * @Date: 2021-10-09 17:27:44
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-09 23:59:01
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "main.h"

void test_heap()
{
    printf("---- Start heap test ----\n");

    Miniheap *pHeap = heap_init();
    heap_insert(pHeap, 3, INT_MAX);
    heap_insert(pHeap, 6, 100);
    heap_insert(pHeap, 2, 20);
    heap_insert(pHeap, 8, 3);
    heap_insert(pHeap, 4, 1);
    heap_print(pHeap);
    heap_print_indexes(pHeap);
    HeapNode *node6 = heap_get_node(pHeap, 3);
    HeapNode *parentNode = node6->parent;
    printf("index: %d\n", parentNode->index);

    heap_free(pHeap);

    printf("----- End heap test -----\n");
}

void test_graph()
{
    printf("---- Start graph test ----\n");

    Graph *pgraph = graph_init(7, 0);
    graph_add_edge(pgraph, 1, 2, 1);
    graph_add_edge(pgraph, 1, 5, 1);
    graph_add_edge(pgraph, 1, 6, 1);
    graph_add_edge(pgraph, 1, 0, 1);
    graph_add_edge(pgraph, 3, 0, 1);
    graph_add_edge(pgraph, 3, 4, 1);
    graph_add_edge(pgraph, 5, 7, 1);
    graph_add_edge(pgraph, 5, 2, 1);
    graph_add_edge(pgraph, 7, 2, 1);
    graph_add_edge(pgraph, 3, -1, 1);
    graph_add_edge(pgraph, 5, 6, 1);
    graph_add_edge(pgraph, 2, 6, 1);
    graph_print(pgraph);
    graph_free(pgraph);

    printf("----- End graph test -----\n");
}



int main(int argc, char const *argv[])
{
    test_heap();
    test_graph();
    return 0;
}