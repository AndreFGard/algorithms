#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tablesize_start 11
#define previously_busy 2
#define empty  1
#define full 0


typedef struct slot_t {
    unsigned char stat;
    int value;
} slot_t;

typedef struct hashtable {
    int curr_size;
    int max_size;
    slot_t *table;
} hashtable;

int hash(int value, int size){
    return (value*value)%size;
}


void populate_table_arr(hashtable *t, slot_t *arr){
    for (int i = 0; i<t->max_size; i++){
        arr[i].stat = empty;
    }
}

//linear probing conflict resolution
int insert_l(hashtable *t, int value) {
    int tablesize = t->max_size;
    int k = hash(value, tablesize);
    slot_t *s = &t->table[k];
    if (s->stat != full){
        s->value = value;
        s->stat = full;
        t->curr_size++;
    }
    else if (t->curr_size != t->max_size){  //if not full
        int i = (k +1)%tablesize;

        for(;; i = (i+1)%tablesize){    //search for next empty (change this for a while)
            s = &t->table[i];
            if (s->stat != full){
                s->value = value;
                s->stat = full;
                t->curr_size++;
                break;
            }
        }
        k = i;
    }
    else {
        //the table is full, resize it
        puts("no thanks, im full");
        s = (slot_t*) malloc(sizeof(slot_t)*t->max_size*2);

        t->max_size *= 2;
        populate_table_arr(t, s);
        memcpy(s, t->table, sizeof(slot_t)*t->curr_size);
        k = insert_l(t, value);
    }
    return k;
}


void populate_table(hashtable *t){
    t->curr_size = 0;
    t->max_size = tablesize_start;
    t->table = malloc(sizeof(slot_t)*tablesize_start);
    populate_table_arr(t, t->table);
}

int main() {
    hashtable table;
    populate_table(&table);
    for (int i = 0; i < 13; i++){
        insert_l(&table, i);
    }


    puts("eae!");
}