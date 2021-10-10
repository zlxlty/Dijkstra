/*
 * @Author: Tianyi Lu
 * @Description: 
 * @Date: 2021-10-09 19:52:23
 * @LastEditors: Tianyi Lu
 * @LastEditTime: 2021-10-09 23:53:48
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct _graph {
    int initNum;
    int numNodes;
    int **edges;
} Graph;

Graph *graph_init(int numNodes, int initNum);
void graph_add_edge(Graph *pgraph, int startVertexIndex,
                    int endVertexIndex, int value);
int graph_get_edge(Graph *pgraph, int startVertexIndex, int endVertexIndex);
void graph_delete_edge(Graph *pgraph, int startVertexIndex, int endVertexIndex);
void graph_print(Graph *pgraph);
void graph_free(Graph *pgraph);

#endif
