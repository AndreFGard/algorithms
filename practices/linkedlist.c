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


// void increase_freelist(node *freelist) {
//     watchme += 1;
//     freelist->next = malloc(sizeof(node)*minfreelistsize);

//     //delimitando o final da free (nodes) list
//     freelist->next[minfreelistsize -1].next = NULL; // isso nao causa segfault
//     freelist->next[minfreelistsize -1].data = watchme; // isso nao causa segfault
//     //(freelist->next + (minfreelistsize -1))->next = NULL; //isso causa segfault

//     freelist->next->next = freelist->next + sizeof(node); //there is enough space.
// }

#define IDK 97
int counter = 0;
node *temp;
List freelist;


node* _makeFreeNode() {
    return malloc(sizeof(node));
}

node* getFreeNode(){
    if (!freelist.size){
        counter++; 
        return _makeFreeNode();
    }

    temp = freelist.head->next;
    freelist.head->next = freelist.head->next->next;
    freelist.size--;
    temp->next = NULL; // just for safety
    return temp;

    }
void* insertNode(List *l, node *node) {
    if (l->tail == l->curr) l->tail = temp;
    temp->next = l->curr->next;
    l->curr->next = temp;
    l->size++;

}
void* addNode(List *l,datatype data) {
    temp = getFreeNode();
    insertNode(l, temp);
    temp->data = data;
}

void prepare_list(List *l){
    l->head = l->tail = l->curr = getFreeNode();
    l->head->next = NULL;
    l->size = 0;
}

void create_freelist(List *l){

}

node *remove_node(List *l){
    if (l->curr->next == NULL) return NULL;
    temp = l->curr->next;
    if (l->tail == l->curr->next) l->tail = l->curr;
    l->curr->next = temp->next; l->size--;
    //get rid of temp
    insertNode(&freelist, temp);
    return temp;

}

void __freeFreelistNode(void *node);

void freeFreeList(List *l){
    freelist.curr = freelist.head;
    while (temp = freelist.curr){
        freelist.curr = freelist.curr->next;
        free(temp);
    }
}

int main()  {
    freelist.size = 0;
    prepare_list(&freelist);
    List l;
    prepare_list(&l);
    int i = 0;
    int size = 600000;
    for (i = 0; i<size; i++){
        addNode(&l, i);
        l.curr = l.curr->next;
    }

    l.curr = l.head;
    for (;l.size;){
        if (!remove_node(&l)) printf("something has gone wrong with i %d\n", i);
        //free(l.head);
    }
    free(l.head);
    freeFreeList(&freelist);

    printf("last data held is %d and malloc was called %d times\n", (&counter), counter);
    puts("hello");
}
