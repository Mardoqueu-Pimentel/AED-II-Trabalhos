#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int x, y; } edge_t;
typedef struct graph * graph_t;

typedef enum graph_Opt {
	graph_OptYes, graph_OptNo
} graph_Opt;

extern graph_Opt graph_Print;
extern graph_Opt graph_AllPaths;

// Constructors/Destructors
graph_t graph_new (int V);
graph_t graph_delete (graph_t G);

// Métodos
bool graph_isConnected (graph_t G);
void graph_fprint (graph_t G, FILE *fptr);
void graph_push (graph_t G, edge_t e);
void graph_randomize (graph_t G, float connectivity);

// Caminhamentos
void graph_bfs (graph_t G, int from);
void graph_dfs (graph_t G, int from);
void graph_paths (graph_t G, int from);

#endif