#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define tablesize_start 8
#define previously_busy 2
#define empty  1
#define full 0

int tablesize = 8;
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
    return value - (size * floor(value/size));
}


void populate_table_arr(hashtable *t, slot_t *arr){
    for (int i = 0; i<t->max_size; i++){
        arr[i].stat = empty;
    }
}

//linear probing conflict resolution
int insert_l(hashtable *t, int value) {
    tablesize = t->max_size;
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
        return k;

        //forgot to do rehashing, not worth it
        s = (slot_t*) malloc(sizeof(slot_t)*t->max_size*2);

        t->max_size *= 2;
        populate_table_arr(t, s);
        memcpy(s, t->table, sizeof(slot_t)*t->curr_size);
        k = insert_l(t, value);
    }
    return k;
}


int find_l(hashtable *t, int value) {
    tablesize = t->max_size;
    int k = hash(value, tablesize);
    int i = k;

    int found_at = -1;
    do {
        if (t->table[i].stat != empty) {
            //one must consider the previously busy case
            if (t->table[i].value == value && t->table[i].stat !=previously_busy) {
                found_at = i; 
                break;
            }
            i = (i+1)%tablesize;
        }
        else {
            break;
        }
    }
    while (i != k);
    return found_at;
}

int remove_l(hashtable *t, int value){
    tablesize = t->max_size;
    int idx = find_l(t, value);
    if (idx != -1){
        t->curr_size -=1;
        t->table[idx].stat = previously_busy;
        return idx;
    }
    return -1;

}

void populate_table(hashtable *t){
    t->curr_size = 0;
    t->max_size = tablesize_start;
    t->table = (slot_t *)malloc(sizeof(slot_t)*tablesize_start);
    populate_table_arr(t, t->table);
}

int test_linear() {
    hashtable table;
    populate_table(&table);
    for (int i = 0; i < 13; i++){
        insert_l(&table, i);
    }

    remove_l(&table, 9);
    find_l(&table, 12);

    for (int i = 0; i < 13; i++){
        if (find_l(&table, i) == -1){
            printf("couldnt find value %d\n", i);
        }
    } 
        populate_table(&table);
    for (int i = 0; i < 13; i++){
        insert_l(&table, i);
    }
    for (int i = 0; i < 13; i++){
        if (find_l(&table, i) == -1){
            printf("couldnt find value %d\n", i);
        }
    } 
    puts("eba, salvei e guardei tudo!");
    return 1;
}


/////random probing hashtable


int deal_colision_hash(int k){ return (k + k*((tablesize-2-k)%(tablesize-2)))%tablesize;}

//#define deal_colision_hash (k + randints[i])%tablesize


int randints[] = {0, 2, 6, 7, 3, 1, 4, 5};
int insert_r(hashtable *t, int value) {
    tablesize = t->max_size;
    int k = hash(value, tablesize);

    if (t->curr_size == t->max_size){
        puts("n cabe nao"); return -1;
    }else

    //this for does reach every position, please note, because the randints
    //are all between 0 and tablesize and have no repetition
    for (int i = 0; i<tablesize; i++){
        if (t->table[   deal_colision_hash(k)  ].stat != full){
            k = deal_colision_hash(k);
            //one could check if we arent repeating an item right here
            t->table[k].value = value;
            t->table[k].stat = full;
            t->curr_size++;
            return k;
        }
    }
    return 1;
}

int find_r(hashtable *t, int value){
    tablesize = t->max_size;
    int k = hash(value, tablesize);

    //this for does reach every position, please note, because the randints
    //are all between 0 and tablesize and have no repetition
    for (int i = 0; i<tablesize; i++){
        if (t->table[   deal_colision_hash(k)  ].stat != empty){
            
            //one could check if we arent repeating an item right here
            if (t->table[   deal_colision_hash(k)  ].value == value && t->table[   deal_colision_hash(k)  ].stat != previously_busy){
                k = deal_colision_hash(k);
                return k;
            }
        }
        else{
            // nao esta aqui, bye bye
            break;
        }
    }    

    return -1;
}


int main(){
    hashtable table;
    populate_table(&table);

    hashtable *t = &table;



    int nums[] = {2, 4, 8, 16, 32, -12,78};
    for (int i = 0; i < 6; i++){
        insert_r(&table, nums[i]);
    }

    for (int i = 0; i <7; i++){
        if (find_r(t, nums[i]) == -1){
            printf("nao achei %d\n", nums[i]);
        }
    }

    for (int i = 0; i < 8; i++){
        printf("%d at %d\n",table.table[i].value, i);
    }
    puts("eae");
}