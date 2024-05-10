#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct  node{
    datatype *data;
    struct node *next;
} node;

#define minfreelistsize 3

int freelist_size;
node *freelist; //lista com nodes livres
node *temp;
int watchme = 50;
void increase_freelist() {
    freelist->next = malloc(sizeof(node)*minfreelistsize);

    //delimitando o final da free (nodes) list
    freelist->next[minfreelistsize -1].next = NULL; // isso nao causa segfault
    freelist->next[minfreelistsize -1].data = &watchme; // isso nao causa segfault
    (freelist->next + (minfreelistsize -1))->next = NULL; //isso causa segfault

    freelist->next->next = freelist->next + sizeof(node); //there is enough space.
}


node* get_free_node() {
    //gets free node from the free (nodes) list
    if (freelist->next->next != NULL) {
        temp = freelist->next;
        freelist->next = &freelist->next[1];
    }
    else {
        //after temp, the next is the last node.
        temp = freelist->next; 
        
        freelist->next = &freelist->next[1];
        increase_freelist();
        
    }
    
    return temp;
}

#define movecurrent() head->

node* addNode(node *curr, datatype *data) {
    //inserts right next to the current
    temp = get_free_node();
    temp->data = data;
    temp->next = curr->next;
    curr->next = temp;
}

int main()  {
    freelist = alloca(sizeof(node));
    increase_freelist();
    int stuff = 99999;
    node *head = get_free_node();
    node *curr = head;
    for(int i = 0;i<50; i++){
        curr->next = get_free_node();
        //curr->next->data = &stuff;
        curr = curr->next;
    }
    puts("hello");
}
