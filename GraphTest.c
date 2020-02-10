// Name: Ruben Calderon
// CruzID: rucalder
// Date: December 6, 2019
// Pa5

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"
#include <string.h>

int main(int argc, char* argv[]){

	Graph G = newGraph(5);
	
	addArc(G, 1, 2);
	addArc(G, 3, 4);
	addArc(G, 1, 3);
	addArc(G, 2, 4);
	addArc(G, 3, 2);
	addArc(G, 4, 5);

	printGraph(stdout, G);
	//printf("%d\n", getParent(G, 1));
	
	printf("Running DFS, source 1\n");
	List S = newList();
	append(S, 1); append(S, 2); append(S, 3); append(S, 4); append(S, 5);
	printf("S before DFS: ");
	printList(stdout, S);
	printf("\n");
	DFS(G, S);
	printf("S after DFS: ");
	printList(stdout, S);
	printf("\n");
	printf("Discovery times: ");
	printf("\n");
	for(int i = 1; i <= getOrder(G); i++){
		printf("%d: %d, %d\n", i, getDiscover(G, i), getFinish(G, i));
	}
	printf("Parent of 1: %d\n", getParent(G, 1));
	printf("Parent of 2: %d\n", getParent(G, 2));
	printf("Parent of 5: %d\n", getParent(G, 5));
	printf("Size of G: %d\n", getSize(G));

	freeList(&S);
	freeGraph(&G);
	return(0);
}
