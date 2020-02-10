// Name: Ruben Calderon
// CruzID: rucalder
// Date: DEcember 6, 2019
// Pa5


#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include"List.h"

#define UNDEF -99
#define NIL 0

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List s);
void Visit(Graph G, int x, int* time, List tempList);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
Graph transpose(Graph G);
Graph copyGraph(Graph G);

#endif
