#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define occupied -5
#define prev_occupied -4
#define empty -3


// long int floor (double n){
//     return ((long int) n);
// }



typedef struct {
    int value;
    int key;
    int stat;
} data;

typedef struct{
    int size;
    data *arr;
} hashtable;

int m;
int hash_old(int n){
    return n - (m * floor(n/m));
}

int hash(int key) {
    int mod = m;
    int temp = (int) floor((((double) key) / ((double) mod)));
    return (key - (mod * temp));
}

int *perm;
int find(hashtable *t, int key){
    int k = hash(key);
    int newpos = 0;
    if (t->size > 0){
        for(int i = 0; i<m;i++){
            newpos = (k + perm[i])%m;
            if(t->arr[newpos].stat == empty){
                return -1;
            }
            else if (t->arr[newpos].stat == occupied){
                //se está ocupado
                if (t->arr[newpos].key == key){
                    //achamos
                    return newpos;
                }
                //não achamos ainda
            }

            //se for previously occupied, apenas continuar
        }


    }
    return -1;

}

int add(hashtable *t, int key, int value){
    int k = hash(key);
    int newpos;
    int found = find(t, key);
    if (found != -1) {
        //ele ja esta aqui
        return -1;
    }
    if (t->size < m){
        for (int i = 0; i<m;i++){
            newpos = (k + perm[i])%m;
            if (t->arr[newpos].stat == empty || t->arr[newpos].stat == prev_occupied ){
                t->arr[newpos].value = value;
                t->arr[newpos].key = key;
                t->arr[newpos].stat = occupied;
                t->size++;
                return newpos;
            }
        }
    }
    return -1;
}

void populate(hashtable *t){
    t->arr = (data*) malloc(sizeof(data) * m);
    t->size = 0;
    for (int i = 0; i <m; i++){
        t->arr[i].stat = empty;
        t->arr[i].key = t->arr[i].value = 0;
    }   
}


int main() {
    m = 0;
    int nops = 0;
    char command[70];

    scanf("%d", &m);
    while(m){
        if ((m) == 0) break;
        perm = (int *) malloc(sizeof(int)* m);
        perm[0] = 0;

        for (int i = 0; i<m-1; i++) {
            scanf("%d", &perm[i+1]);
        }

        hashtable t;
        populate(&t);



        int tempk, tempv, pos;
        scanf("%d", &nops);
        for(int i = 0; i<nops; i++) {
            scanf("%s", command);
            
            if (strncmp("add", command, 3) == 0){
                scanf("%d %d", &tempk, &tempv);
                add(&t, tempk, tempv );
            }
            else{
                //find
                scanf("%d", &tempk);
                pos = find(&t, tempk);
                if (pos != -1)
                    {printf("%d %d\n", pos, t.arr[pos].value);}
                else {
                    printf("%d\n", pos);
                }
            }
        }
    scanf("%d", &m);
    }

}