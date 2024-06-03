#define tablesize 101
#define full 0
#define empty 1
#define previously_full 2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int stat;
    char *s;
} member;

typedef struct {
    int size;
    member arr[tablesize+1];
} hashtable;

int hash (char key[]){
    long int sum = 0;
    for (int i = 0; i<17; i++)
    {
        if (key[i] == '\0') {
            break;
        }
        sum += key[i]*(i+1);
    }
    return (sum*19)%tablesize;
}

int find(hashtable *t, char key[]) {
    int k = hash(key);
    int newpos = -1;
    int _;
    for (int i = 0; i<20; i++){
        newpos = (k + i*i + 23*i)%tablesize;

        if (t->arr[newpos].stat == full) {
            if (strcmp(key, t->arr[newpos].s) == 0){
                // se são iguais. se não forem continuar 
                return newpos;
            }
        }
        else if (t->arr[newpos].stat == empty){
            //não achamos :(
            return -1;
        }
        else if (t->arr[newpos].stat == previously_full){
            _ = 0; // nao fazer nada
        }
    }

    return -1;
}

int insert(hashtable *t, char key[]) {
    int k = hash(key);
    int newpos = -1;

    //menos arriscado fazer assim
    int found = find(t, key);
    if (found == -1){
        for (int i =0; i<20; i++){
            newpos = (k + i*i + 23*i)%tablesize;

            //checar mesmo assim se ja nao foi inserido
            if (strcmp(t->arr[newpos].s, key) == 0 && t->arr[newpos].stat == full) {
                return -1;
            }
            if (t->arr[newpos].stat != full){
                //já sabemos que não está inserido na tabela,podemos insereir
                t->arr[newpos].s = key;
                t->arr[newpos].stat = full;
                t->size++;
                return newpos;
            }

        }
    }
    return -1;

}

int del_k(hashtable *t, char key[]){
    int pos = find(t, key);
    if (pos != -1){
        t->arr[pos].stat = previously_full;
        t->size--;
    }
    return pos;
}

char empty_str[] = {19, '\0'}; //tentando evitar colisles com isso, por garantia
int populate_table(hashtable *t) {
    t->size = 0;
    for (int i = 0; i < tablesize; i++){
        t->arr[i].stat = empty;
        t->arr[i].s = empty_str;
    }
    return 0;
}

int main() {

    
    int n, nops;
    scanf("%d %d", &n, &nops);
    char *newstr;
    hashtable *t;

    t = (hashtable *) malloc(sizeof(hashtable));
    populate_table(t);

    for (int c = 0; c<n; c++){
        t = (hashtable *) malloc(sizeof(hashtable));
        populate_table(t);
        for(int i = 0; i<nops; i++){
            newstr = (char *) malloc(16+4);
            scanf("%s", newstr);
            
            if (strncmp("ADD:", newstr, 4) == 0){
                //garantir que é add, vai que a questão trola
                newstr = newstr + 4;
                insert(t, newstr);
            }
            else if (strncmp("DEL:", newstr, 4)==0){
                newstr = newstr+4;
                del_k(t, newstr);
            }
            //else if(strcmp("st", newstr) == 0) break;

        }
        printf("%d\n", t->size);
        for (int k = 0; k<tablesize; k++){
            if (t->arr[k].stat == full){
                printf("%d:%s\n", k, t->arr[k].s);;
            }
        }

    }

}