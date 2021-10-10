/*
 * @Author: Tianyi Lu
 * @Description:
 * @Date: 2021-10-09 19:52:19
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-09 23:54:06
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph *graph_init(int numNodes, int initNum)
{
    Graph *pgraph = (Graph *)malloc(sizeof(Graph));
    pgraph->initNum = initNum;
    pgraph->numNodes = numNodes;
    pgraph->edges = (int **)malloc(sizeof(int *) * pgraph->numNodes);

    for (int i = 0; i < pgraph->numNodes; i++)
    {
        pgraph->edges[i] = (int *)malloc(sizeof(int) * pgraph->numNodes);
        memset(pgraph->edges[i], initNum, pgraph->numNodes * sizeof(int));
    }

    return pgraph;
}

void graph_add_edge(Graph *pgraph, int startVertexIndex,
                    int endVertexIndex, int value)
{
    if (startVertexIndex < 0 || startVertexIndex >= pgraph->numNodes ||
        endVertexIndex < 0 || endVertexIndex >= pgraph->numNodes)
    {
        return;
    }

    pgraph->edges[startVertexIndex][endVertexIndex] = value;
}

int graph_get_edge(Graph *pgraph, int startVertexIndex, int endVertexIndex)
{
    if (startVertexIndex < 0 || startVertexIndex >= pgraph->numNodes ||
        endVertexIndex < 0 || endVertexIndex >= pgraph->numNodes)
    {
        return 0;
    }

    return pgraph->edges[startVertexIndex][endVertexIndex];
}

void graph_delete_edge(Graph *pgraph, int startVertexIndex, int endVertexIndex)
{
    if (startVertexIndex < 0 || startVertexIndex >= pgraph->numNodes ||
        endVertexIndex < 0 || endVertexIndex >= pgraph->numNodes)
    {
        return;
    }

    pgraph->edges[startVertexIndex][endVertexIndex] = pgraph->initNum;
}

void graph_print(Graph *pgraph)
{
    if (!pgraph)
        return;

    printf("num of vertices: %d\n", pgraph->numNodes);
    printf("init number: %d\n", pgraph->initNum);
    printf("-----------------------------\n");
    for (int i = 0; i < pgraph->numNodes; i++)
    {
        printf("Vertex %2d:\n", i);
        for (int j = 0; j < pgraph->numNodes; j++)
        {
            int value = pgraph->edges[i][j];
            if (value != 0)
                printf("Edge %2d -> %2d: %d\n", i, j, value);
        }
        printf("-----------------------------\n");
    }
}

void graph_free(Graph *pgraph)
{
    if (pgraph == NULL || pgraph->edges == NULL)
        return;

    for (int i = 0; i < pgraph->numNodes; i++)
        free(pgraph->edges[i]);

    free(pgraph->edges);
    free(pgraph);
}