// Name: Ruben Calderon
// CruzID: rucalder
// Date: December 6, 2019
// Pa5


#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"


int main(int argc, char* argv[]){

        if(argc != 3){
                fprintf(stderr, "Error: Incorrect amount of command line arguments.\n");
                exit(1);
        }

        FILE* in;
        FILE* out;
        in = fopen(argv[1], "r");
        out = fopen(argv[2], "w");
        if(in == NULL){
                fprintf(stderr, "Error: input file not found.\n");
                exit(1);
        }

        int numV;
        fscanf(in, "%d\n", &numV);
        Graph G = newGraph(numV);

	int v1;
        int v2;
        int t =1;
        while(t == 1){
                fscanf(in, "%d %d\n", &v1, &v2);
                if(v1 == 0 && v2 == 0){
                        break;
                }

                addArc(G, v1, v2);
        }
	
	fprintf(out, "Adjacency list representation of G:\n");
	/*for(int i = 0; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		for(int j = 1; j <= getOrder(G); i++){
			fprintf(out, "%d ", 
	}*/
	printGraph(out, G);
	fprintf(out, "\n\n");
	
	List S = newList();
	for(int i = 1; i <= numV; i++){
		append(S, i);
	}
	DFS(G, S);
	//printList(stdout, S);
	moveFront(S);
	//printf("After move front");
	int SCC = 0;
	Graph Gt = transpose(G);
	DFS(Gt, S);
	moveFront(S);
	//printf("after transpose");
	while(index(S) != -1){
		if(getParent(Gt, get(S)) == NIL){
			SCC++;
		}
		moveNext(S);
	}
	printf("%d\n", SCC);
	List* Components = calloc(SCC+1, sizeof(List));
	for(int i = 1; i <= SCC; i++){
		Components[i] = newList();
	}
	//printf("after Components\n");
	moveBack(S);
	//List Strong = newList();
	int i = 1;
	while(index(S) != -1){
		int x = get(S);
		//prepend(Components[i], x);
		
		prepend(Components[i], x);
		if(getParent(Gt, x) == NIL){
			i++;
		}
		movePrev(S);
		//movePrev(S);
	}
	//printf("after arranging Components\n");
	fprintf(out, "G contains %d strongly connected components:\n", SCC);
	for(int j = 1; j <= SCC; j++){
		fprintf(out, "Component %d : ", j);
		printList(out, Components[j]);
		fprintf(out, "\n");
	}
	
	freeGraph(&G);
	return(0);
}












