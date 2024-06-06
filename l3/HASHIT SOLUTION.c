#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define occupied -5
#define prev_occupied -4
#define unused -3
#define tablesize 101

// long int floor (double n){
//     return ((long int) n);
// }

typedef struct {
    char *s;
    int stat;
} member;

typedef struct{
    int size;
    member *arr;
} hash_ktable;

int m;
int hash_k_old(int n){
    return n - (m * floor(n/m));
}

int hash_k (char key[]){
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

int find(hash_ktable *t, char key[]){
    //escanear com força bruta ao inves de usar as posicoes possiveis de verdade
    //pra garantir que é impossível (espero eu) não achar algo
    if (t->size > 0){
        for (int i =0; i<tablesize; i++){
            if (t->arr[i].stat == occupied){
                if (strcmp(t->arr[i].s, key) == 0){
                    return i;
                }
            }
        }
    }
    return -1;
}

int add(hash_ktable *t, char key[]){
    int found = find(t, key);
    int k = hash_k(key);
    int newpos = 0;

    //se nao for achado
    if (found == -1 && t->size < tablesize){
        for (int i =0;i<=19; i++){
            newpos = (k + i*i + 23*i)%tablesize;
            if (t->arr[newpos].stat != occupied){
                t->arr[newpos].stat = occupied;
                t->arr[newpos].s = key;
                t->size++;
                return newpos;
            }
        }
    }
    return -1;
}

int del_k(hash_ktable *t, char key[]){
    int found = find(t, key);
    if (found != -1){
        //esse marcador não está sendo usado no momento devido ao find atual,
        //que usa "força bruta" ao invés de parar quando achar o primeiro unused
        // ou o primeiro igual
        t->arr[found].stat = prev_occupied;
        t->size--;
    }
    return found;
}

char unused_str[] = {'\0'}; //tentando evitar colisoes com isso, por garantia
int populate_table(hash_ktable *t) {
    t->size = 0;
    t->arr = (member *)malloc(sizeof(member)*tablesize);
    for (int i = 0; i < tablesize; i++){
        t->arr[i].stat = unused;
        t->arr[i].s = unused_str;
    }
    return 0;
}

int main() {

    
    int n, nops;
    scanf("%d", &n);
    hash_ktable *t;

    t = (hash_ktable *) malloc(sizeof(hash_ktable));
    populate_table(t);

    for (int c = 0; c<n; c++){
        scanf("%d", &nops);
        t = (hash_ktable *) malloc(sizeof(hash_ktable));
        //limpar e preparar a tabela
        populate_table(t);
        
        for(int i = 0; i<nops; i++){
            char *newstr = (char*)malloc(100);
            scanf("%s", newstr);

            if (strncmp(newstr, "ADD:", 4) == 0){
                newstr = newstr + 4;
                add(t, newstr);
            }
            else if (strncmp(newstr, "DEL:", 4) == 0){
                newstr = newstr + 4;
                del_k(t, newstr);
            }

        }
        printf("%d\n", t->size);
        for (int i =0; i<tablesize;i++){
            if (t->arr[i].stat == occupied){
                printf("%d:%s\n", i, t->arr[i].s);

            }
        }


    }

}