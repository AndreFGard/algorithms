#include <stdlib.h>
#include <stdio.h>
typedef struct node {
    struct node *next;
    int data;
} node;

typedef struct list {
    int size;
    node *head;
    node *tail;
} list;

node *get_node() {
    node *temp;
    temp = (node*) malloc(sizeof(node));
    temp->next = NULL;
    return temp;
}

int add_node(list *l, int value){
    int i;
    node *temp;
    temp = (node*) malloc(sizeof(node));
    temp->data = value;

    l->tail->next = temp;
    temp->next = NULL;
    
    l->tail = temp;
    l->size++;

    return 1;
}

void obliterate_next_node(list *l, node *byebye){
    node *temp = byebye->next;
    byebye->next = temp->next;
    l->size--;

    if(temp == l->tail) l->tail = l->head;
    free(temp);
}

#define tablesize 11
typedef struct hashtable{
    int size;
    list table[11];
}hashtable;

node *add_head(list *l) {
    node *temp = get_node();
    l->tail = l->head = temp;
    l->size = 0;
    return temp;
}

int mylog10(int n) {
    int log = 0;
    // Assume n has initial value N
    while ( n >= 10 ) {
        // Invariant: N = n * 10^log
        n /= 10;
        log += 1;
    }
    return log;
}

int populate_table(hashtable *table) {
    int i;
    for ( i = 0; i<tablesize; i++) {
        add_head(&table->table[i]);
    }
    return i;
}

int hash(int value, int table_size) {
    value = value*value*value;
    //int digits = mylog10(table_size) -1;
    return value % table_size;
    /*
    int digits = (int) log10(table_size -1);

    
    */
}

int add_to_table(hashtable *table, int value){
    int key = hash(value, 11);
    list *slot = &table->table[key];
    node *head = slot->head;
    return add_node(slot, value);

}
//returns the node previous to the searched one | NULL
node *find_value(hashtable *table, int value) {
    int key = hash(value, tablesize);
    list *slot = &table->table[key];
    node *curr = slot->head;

    if (curr != slot->tail)
    do {
        if (curr->next->data == value) {
            return curr;
        }
        curr = curr->next;
    }
    while (curr != slot->tail);

    return (node*) NULL;
}

int *remove_value(hashtable *t, int value) {
    node *curr;
    int key = hash(value, 11);
    if (curr = find_value(t, value))
        obliterate_next_node(
            &t->table[key], curr);
    return (int*) curr;
}

int main() {
    hashtable table;
    populate_table(&table);
    for (int i = 0; i < 30; i++){
        add_to_table(&table, i);
    }


    for (int i = 0; i < 30; i++){
        if(!find_value(&table, i)) {
            printf("perdi o %d\n", i);
        }
    }

    int i = 0;
    for (i = 0; i < 32; i++){

        
        if(!remove_value(&table, i) || find_value(&table, i)) {
            printf("couldnt remove %d\n", i);
            fflush(stdout);
        }
    }
    puts("eae!");
}