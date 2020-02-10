// Name: Ruben Calderon
// CruzID: rucalder
// Date: December 6, 2019
// Pa5


#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"


typedef struct GraphObj{
        List* adjList;
	int order;
	int size;
	int source;
	int* color;
        int* p;
        int* d;
	int* f;
}GraphObj;

Graph newGraph(int n){

        Graph G = malloc(sizeof(GraphObj));

        G->adjList = calloc(n+1, sizeof(List));

        for(int i = 1; i <= n; i++){
                G->adjList[i] = newList();
        }

	//G->color = (int*)calloc(n+1, sizeof(int));
	//G->p = 
	
	G->color = calloc(n+1, sizeof(int));
	G->p = calloc(n+1, sizeof(int));
	G->d = calloc(n+1, sizeof(int));
	G->f = calloc(n+1, sizeof(int));

	G->order = n;
	G->size = 0;
	G->source = NIL;
	for(int i = 1; i <= G->order; i++){
		G->p[i] = NIL;
		G->d[i] = UNDEF;
		G->f[i] = UNDEF;
	}	

        return(G);
}

void freeGraph(Graph* pG){
	if(pG!=NULL && *pG!=NULL){
                for(int i = 1; i <= (*pG)->order; i++){
                        freeList(&((*pG)->adjList[i]));
                }
                free((*pG)->adjList);
                free((*pG)->color);
		free((*pG)->p);
		free((*pG)->d);
		free((*pG)->f);
		free(*pG);
                *pG=NULL;
        }

}

/*** Access functions ***/
// getOrder
// returns order, or number of vertices, of graph
int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getOrder on null graph\n");
		exit(1);
	}
	
	return G->order;
}

// getSize
// returns size, or number of edges, of graph
int getSize(Graph G){
	if(G == NULL){
                printf("Graph Error: calling getSize on null graph\n");
                exit(1);
        }
	return G->size;
}

// getParent
// returns parent of vertex u
int getParent(Graph G, int u){
	if(G == NULL){
                printf("Graph Error: calling getParent on null graph\n");
                exit(1);
        }
	if(u < 1 || u > G->order){
		printf("Graph Error: calling getParent on invalid index\n");
                exit(1);
        }
	//if(G->source == NIL){
	//	return NIL;
	//}
	return (G->p[u]);
}

// getDiscover(Graph G, int u)
// returns discovery time of vertex u
int getDiscover(Graph G, int u){
	if(G == NULL){
                printf("Graph Error: calling getDiscover on null graph\n");
                exit(1);
        }
	return(G->d[u]);
}

// getFinish(Graph G, int u)
// returns finish time of vertex u
int getFinish(Graph G, int u){
	if(G == NULL){
                printf("Graph Error: calling getFinish on null graph\n");
                exit(1);
        }
	return(G->f[u]);
}


/*** Manipulation procedures ***/
// addEdge
// inserts a new edge joining u to v. u is added to list of v, and vice verse.
// Must be inserted in sorted order
// pre: u and v be between 1 and order
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge on null graph\n");
                exit(1);
        }
	if(u < 1 || u > G->order){
		printf("Graph Error: calling addEdge on out of bounds u\n");
                exit(1);
        }
	if(v < 1 || v > G->order){
                printf("Graph Error: calling addEdge on out of bounds v\n");
                exit(1);
        }
	List listU = G->adjList[u];
	List listV = G->adjList[v];
	
	moveBack(listU);
	moveBack(listV);

	while(index(listU) != -1){
		if(get(listU) > v){
			if(index(listU) == 0){
				insertBefore(listU, v);
				moveFront(listU);
				movePrev(listU);
			}
			movePrev(listU);
		}
		else{
			insertAfter(listU, v);
			moveFront(listU);
			movePrev(listU);
		}
	}
	
	while(index(listV) != -1){
                if(get(listV) > u){
                        if(index(listV) == 0){
                                insertBefore(listV, u);
                                moveFront(listV);
                                movePrev(listV);
                        }
                        movePrev(listV);
                }
                else{
                        insertAfter(listV, u);
                        moveFront(listV);
                        movePrev(listV);
                }
        }


	
	if(length(listU) == 0){
		prepend(listU, v);
	}
	if(length(listV) == 0){
		prepend(listV, u);
	}
	G->size++;
}	


// addArc
// inserts a new directed edge from u to v. v is added to list of u.
// pre: u and v be between 1 and order
void addArc(Graph G, int u, int v){
	if(G == NULL){
                printf("Graph Error: calling addEdge on null graph\n");
                exit(1);
        }
        if(u < 1 || u > G->order){
                printf("Graph Error: calling addEdge on out of bounds u\n");
                exit(1);
        }
        if(v < 1 || v > G->order){
                printf("Graph Error: calling addEdge on out of bounds v\n");
                exit(1);
        }
        List listU = G->adjList[u];

        moveBack(listU);

        while(index(listU) != -1){
                if(get(listU) > v){
                        if(index(listU) == 0){
                                insertBefore(listU, v);
                                moveFront(listU);
                                movePrev(listU);
                        }
                        movePrev(listU);
                }
                else{
                        insertAfter(listU, v);
                        moveFront(listU);
                        movePrev(listU);
                }
        }
	if(length(listU) == 0){
		prepend(listU, v);
	}
	G->size++;
}




// BFS
// runs BFS algorithm on graph G with source S, setting color, distance, parent, and source fields of G respectively.
void DFS(Graph G, List S){
	if(G == NULL){
                printf("Graph Error: calling DFS() on null graph\n");
                exit(1);
        }
	if(length(S) != G->order){
		printf("Graph Error: calling DFS() on incorrectly sized list\n");
                exit(1);
        }
	for(int i = 1; i <= G->order; i++){
                G->color[i] = 1;
                G->d[i] = UNDEF;
		G->f[i] = UNDEF;
                G->p[i] = NIL;
        }
	int time = 0;
	List temp = copyList(S);
	//List Queue = newList();
        //append(Queue, s);
        clear(S);
	while(length(temp) != 0){
		moveFront(temp);
                int x = get(temp);
                deleteFront(temp);
		if(G->color[x] == 1){
			Visit(G, x, &time, S);
		}
		//deleteFront(S);
	}
	//G->d[s] = 0;
	//G->p[s] = NIL;
	//G->source = s;
	freeList(&temp);
}


void Visit(Graph G, int x, int* time, List tempList){
	(*time)++;
	G->d[x] = *time;
	G->color[x] = 2;
	List adj = G->adjList[x];
	moveFront(adj);
	while(index(adj) != -1){
		int y = get(adj);
		if(G->color[y] == 1){
			G->p[y] = x;
			Visit(G, y, time, tempList);
		}
		moveNext(adj);
	}
	G->color[x] = 3;
	(*time)++;
	G->f[x] = *time;
	prepend(tempList, x);
}	

/*** Other operations ***/
// printGraph
// prints graph lmao what else
void printGraph(FILE* out, Graph G){
	if(G == NULL){
                printf("Graph Error: calling addEdge on null graph\n");
                exit(1);
        }
	List list;
	for(int i = 1; i <= G->order; i++){
		list = G->adjList[i];
		fprintf(out, "%d: ", i);
		moveFront(list);
		printList(out, list);
		/*while(index(list) != -1){
			if(index(list) != (length(list)-1)){
				fprintf(out, "%d, ", get(list));
			}
			else{
				fprintf(out, "%d", get(list));
			}
			moveNext(list);
		}*/
		fprintf(out, "\n");
	}
}

// transpose(Graph G)
// reverses all edges of G
Graph transpose(Graph G){
	if(G == NULL){
                printf("Graph Error: calling transpose() on null graph\n");
                exit(1);
        }	
	Graph new = newGraph(G->order);
	for(int i = 1; i <= G->order; i++){
		moveFront(G->adjList[i]);
		while(index(G->adjList[i]) != -1){ 
			addArc(new, get(G->adjList[i]), i);
			moveNext(G->adjList[i]);
		}
		new->color[i] = 1;
		new->p[i] = NIL;
		new->d[i] = UNDEF;
		new->f[i] = UNDEF;
	}
	
	return (new);
}

Graph copyGraph(Graph G){
	if(G == NULL){
                printf("Graph Error: calling copyGraph() on null graph\n");
                exit(1);
        }
	Graph new = newGraph(G->order);
	
	for(int i = 1; i <= G->order; i++){
		new->adjList[i] = copyList(G->adjList[i]);
	}
	new->size = G->size;
	

	return(new);
}






