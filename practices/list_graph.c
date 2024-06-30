#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define VISITED 1
#define UNVISITED 0

typedef struct node {
	struct node *next;
	int v;
} node;

typedef struct {
	node *head;
	int size;
	node *tail;
	node *cur;
}lhead;

node *get_node(int v){
	node *temp = (node *) malloc(sizeof(node));
	temp->next = NULL;
	temp->v = v;
	return temp;
}

void push( lhead *h, int v){
	node *cur = h->tail;
	node *temp = get_node(v);
	printf("%d pushed\n", v);
	h->tail->next = temp;
	h->tail = temp;
	h->size++;
	return;
}

typedef struct list_graph{
	lhead *m;
	int *mark;
} list_graph;
typedef  list_graph lg;

void prepare_list(lhead *h){
	h->size = 0;
	h->tail = h->head = get_node(69);
	h->cur = NULL;
	
}

list_graph *create_graph(int size){
	lg *temp = (lg*) malloc(sizeof(lg));
	temp->m = malloc(sizeof(lhead)*size);
	temp->mark = malloc(sizeof(int)*size);

	for (int i = 0; i<size;i++){
		temp->mark[i] = UNVISITED;
		prepare_list(&temp->m[i]);
	}
	return temp;
}

void insert_edge(lg *g, int v, int e){
	printf("%d: ", v);
	push(&g->m[v], e);
}

int next(lg *g, int v, int w){
	g->m[v].cur = g->m[v].cur->next;

	if (g->m[v].cur)
		return g->m[v].cur->v;
	else return -1;
}

int first(lg *g, int v){
	g->m[v].cur = g->m[v].head->next;
	if (g->m[v].cur)
		return g->m[v].cur->v;
	else return -1;
}

void setMark(lg *g, int v, int mark){
	g->mark[v] = mark;
}

int getMark(lg *g, int v){
	return g->mark[v];
}

void DFS_l(lg *g, int v){
	setMark(g,v,VISITED);
	int w = first(g, v);
	while (w != -1){
		if (getMark(g,w) == UNVISITED){
			DFS_l(g,w);
		}
		w = next(g,v,0);
	}
	printf("%d ", v); //toposort print

}
#define ie insert_edge 
void test(){
	lg *g = create_graph(15);
	for (int i = 0; i< 15; i++){
		for (int j = 0; j<15; j++){
			if (j!= i){ ie(g, i, j);}
		}	
	}
	DFS_l(g, 0);


}

int main(){

	test();

}





