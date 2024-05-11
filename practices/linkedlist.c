#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct  node{
    datatype data;
    struct node *next;
} node;

typedef struct List {
    node *curr;
    node *tail;
    node *head;
    int size;
}List;

#define minfreelistsize 20

int freelist_size;
List freelist; //lista com nodes livres
node *temp;
int watchme = 0;




// void increase_freelist(node *freelist) {
//     watchme += 1;
//     freelist->next = malloc(sizeof(node)*minfreelistsize);

//     //delimitando o final da free (nodes) list
//     freelist->next[minfreelistsize -1].next = NULL; // isso nao causa segfault
//     freelist->next[minfreelistsize -1].data = watchme; // isso nao causa segfault
//     //(freelist->next + (minfreelistsize -1))->next = NULL; //isso causa segfault

//     freelist->next->next = freelist->next + sizeof(node); //there is enough space.
// }


node* get_free_node() {
    //gets free node from the free (nodes) list
    // if (freelist->next->next != NULL) {
    //     temp = freelist->next;
    //     freelist->next = &freelist->next[1];
    // }
    // else {
    //     //after temp, the next is the last node.
    //     temp = freelist->next; 
        
    //     freelist->next = &freelist->next[1];
    //     increase_freelist();
        
    // }
    temp = malloc(sizeof(node));
    return temp;
}

#define movecurrent() head->

int IMOVER = 6969;
node* addNode(List *l,datatype data) {
    //inserts right net to the current
    node *curr = l->curr;
    temp = get_free_node();
    temp->data = data;
    temp->next = curr->next;
    curr->next = temp;

    if (l->tail == curr) l->tail = temp;
    return temp;
}

void prepare_list(List *l){
    l->curr = get_free_node();
    l->head = l->curr;
    l->tail = l->curr;
}

void create_freelist(List *l){
    prepare_list(l);
    addNode(&freelist, 0);
}

void remove_node(List *l){
    freelist.curr->next = l->curr->next;
    if (l->curr->next == l->tail) l->tail = l->curr;
    l->curr->next = l->curr->next->next;

    freelist.curr = freelist.curr->next;
    freelist.curr->next = NULL;
}

void free_freelist(){
    freelist.curr = freelist.head;
    while ((temp = freelist.curr->next)) {
        free(freelist.curr);
        freelist.curr = temp;
    }
}

int main()  {
    List l;
    prepare_list(&l);
    for (int i = 0; i<50; i++){
        addNode(&l, i);
        l.curr = l.curr->next;
    }
    printf("last data held is %d and freelist was increased %d times\n", (l.curr->data), watchme);
    puts("hello");
}
