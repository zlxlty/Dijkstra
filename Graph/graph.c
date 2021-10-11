/*
 * @Author: Tianyi Lu
 * @Description:
 * @Date: 2021-10-09 19:52:19
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-10 15:52:59
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph *graph_init(int numNodes, int initNum)
{
    Graph *pGraph = (Graph *)malloc(sizeof(Graph));
    pGraph->initNum = initNum;
    pGraph->numNodes = numNodes;
    pGraph->edges = (int **)malloc(sizeof(int *) * pGraph->numNodes);

    for (int i = 0; i < pGraph->numNodes; i++)
    {
        pGraph->edges[i] = (int *)malloc(sizeof(int) * pGraph->numNodes);
        memset(pGraph->edges[i], initNum, pGraph->numNodes * sizeof(int));
    }

    return pGraph;
}

void graph_add_edge(Graph *pGraph, int startVertexIndex,
                    int endVertexIndex, int value)
{
    if (startVertexIndex < 0 || startVertexIndex >= pGraph->numNodes ||
        endVertexIndex < 0 || endVertexIndex >= pGraph->numNodes)
    {
        return;
    }

    pGraph->edges[startVertexIndex][endVertexIndex] = value;
}

int graph_get_edge(Graph *pGraph, int startVertexIndex, int endVertexIndex)
{
    if (startVertexIndex < 0 || startVertexIndex >= pGraph->numNodes ||
        endVertexIndex < 0 || endVertexIndex >= pGraph->numNodes)
    {
        return 0;
    }

    return pGraph->edges[startVertexIndex][endVertexIndex];
}

void graph_delete_edge(Graph *pGraph, int startVertexIndex, int endVertexIndex)
{
    if (startVertexIndex < 0 || startVertexIndex >= pGraph->numNodes ||
        endVertexIndex < 0 || endVertexIndex >= pGraph->numNodes)
    {
        return;
    }

    pGraph->edges[startVertexIndex][endVertexIndex] = pGraph->initNum;
}

void graph_print(Graph *pGraph)
{
    if (!pGraph)
        return;

    printf("num of vertices: %d\n", pGraph->numNodes);
    printf("init number: %d\n", pGraph->initNum);
    printf("-----------------------------\n");
    for (int i = 0; i < pGraph->numNodes; i++)
    {
        printf("Vertex %2d:\n", i);
        for (int j = 0; j < pGraph->numNodes; j++)
        {
            int value = pGraph->edges[i][j];
            if (value != 0)
                printf("Edge %2d -> %2d: %d\n", i, j, value);
        }
        printf("-----------------------------\n");
    }
}

void graph_free(Graph *pGraph)
{
    if (pGraph == NULL || pGraph->edges == NULL)
        return;

    for (int i = 0; i < pGraph->numNodes; i++)
        free(pGraph->edges[i]);

    free(pGraph->edges);
    free(pGraph);
}