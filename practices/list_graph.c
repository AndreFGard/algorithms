#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
	struct node *next
	int v;
} node;

typedef struct {
	node *head;
	int size;
	node *tail;
}lhead;

node *get_node(int v){
	node *temp = (node *) malloc(sizeof(node));
	temp->next = NULL;
	node->v = v;
	return temp;
}

void push( head *h, int v){
	node *cur = h->tail;
	node *temp = get_node(v);

	h->tail->next = temp;
	h->tail = temp;
	return;
}

typedef struct list_graph{
	lhead *m;
	int *mark;
} list_graph;
typedef list_graph lg;

list_graph *prepare_list(lhead *h);

list_graph *create_graph(int size){
	lg *temp = (*lg) malloc(sizeof(lg));
	temp->m = malloc(sizeof(lhead)*size);
	temp->mark = malloc(sizeof(int)*size);

	for (int i = 0; i<size;i++){
		temp->mark[i] = 0;
	}
}