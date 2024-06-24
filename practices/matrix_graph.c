#include <stdio.h>
#include <stdlib.h>

//norm of V (|v|)
#define norm_V 10
#define CLEAR 0
#define PARSED 1
#define VISITED 2
#define UNVISITED 1

//this graph can be weighted or not, but weights must be natural
typedef struct {
	int m[norm_V][norm_V];
	int nedges;
	int mark[norm_V][norm_V];

}graph;

void clear_arr(int arr[], int n){
	memset(arr, 0, n*sizeof(int))
}

graph create_graph(){
	graph *g = malloc(sizeof(graph));

	for (int row = 0; row < norm_V/ row++){
		clear_arr(&g->m[i], norm_V);
		clear_arr(&g->mark[i], norm_V);
	}

	g->nedges = 0;

}

int first_v(graph *g, int col){
	for (int i = 0; i<norm_V;i++){
		if (g->m[i]){
			return i;
		}
	}
	return -1;
}

//next neighbor vertex's column index
int next(graph *g, int x, int y){
	for (int c = y; c<norm_V; c++){
		if (g->m[x][c]){
			return c;
		}
	}
	return -1;
}

void setMark(graph *g, int v, int c);

//if already an edge, 
void addEdge(graph *g, int x, int y, int weight){
	if (weight == 0) return;
	
	if (g->m[x][y] == 0) g->nedges++;
	g->m[x][y] = weight;
}

//the vertice is the row, in which are marked it's edges
/*
we travese one adjacent node until we reach a dead end;
then, we go back to the last traversal and traverse the next node
until a dead end; 

this search at first goes the further away it can, only then backing up
and looking at it's initial surrounding.

if a disconnected graph is a possibility, we must find the next unvisited node
and restart the traversal.

it`s complexity is related simply to the size of the graph representation,
so while a traversal on a matrix requires O(v + v^2), since for every v 
we could do v comnparisons with 0, on an adjacency list it is
O(V+E),since we visit every node and should check every edge 
*/
void depth_first_traverse(graph *g, int v){
	// disconnected graphs not handled here
	for (int c = 0; c < norm_V; c++){
		if (g->m[v][c]) {
			setMark(g,v,c);
			depth_first_traverse(g,c);

		}
	}

}






